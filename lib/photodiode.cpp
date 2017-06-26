#include <algorithm>
#include <complex>
#include <chrono>
#include <fstream>

#include "netxpto.h"
#include "photodiode.h"
#include <random>


void Photodiode::initialize(void){

	firstTime = false;

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

}


bool Photodiode::runBlock(void){

	ofstream myfile2;
	myfile2.open("translate.txt", fstream::app);


	double samplingPeriod = inputSignals[0]->getSamplingPeriod();
	double symbolPeriod = inputSignals[0]->getSymbolPeriod ();
	// [DIA] Bug Correction : introducing (int) avoiding implicit conversion.
	int samplesPerSymbol = (int)round(symbolPeriod / samplingPeriod);

	int ready1 = inputSignals[0]->ready();
	int ready2 = inputSignals[1]->ready();
	int ready = min(ready1, ready2);

	int space = outputSignals[0]->space();

	int process = min(ready, space);

	if (process == 0){
		myfile2.close();
		return false;
	}

	normal_distribution<double> distribution(0, 1);
	double w1 = inputSignals[0]->getCentralFrequency();
	double w2 = inputSignals[1]->getCentralFrequency();
	frequencyMismatch = abs(w1 - w2);
	double noiseAmp1;
	double noiseAmp2;

	double wavelength = inputSignals[0]->getCentralWavelength();


	// [DIA] BUG
	// Correction : introducing (unsigned) avoiding implicit conversion.
	unsigned seed = (unsigned)chrono::system_clock::now().time_since_epoch().count();
	// end bug


	
	generatorAmp1.seed(seed);
	generatorAmp2.seed(seed);

	/*
	// Implementação de filtros gaussianos

	double amp=.5*sqrt(6.4078e-13*5);
	
	
	vector<t_real> gauss;
	gauss.resize(samplesPerSymbol);

	for (int i = 0; i < samplesPerSymbol; i++)
	{
		t_real time = -samplesPerSymbol / 2 * samplingPeriod + i*samplingPeriod;
		gauss[i] = amp*exp(-time*time / (samplingPeriod*samplingPeriod / 36));
	}

	
	if (firstPass)
	{
		firstPass = false;
		for (int i = 0; i < samplesPerSymbol * 8 - samplesPerSymbol / 2; i++)
		{
			t_complex input1;
			inputSignals[0]->bufferGet(&input1);
			t_complex input2;
			inputSignals[1]->bufferGet(&input2);


			t_real power1 = abs(input1) * abs(input1) * 4;
			t_real power2 = abs(input2) * abs(input2) * 4;
			t_real current1 = responsivity * power1;
			t_real current2 = responsivity * power2;
			t_real out = current1 - current2;


			if (out != 0)
			{
				cout << "ERRO: photodiode.cpp (expected output is 0)" << "\n";
				return false;

			}
		}
	}
	*/

	// [DIA] new
	// Power constant for shotNoise.
	t_real P = PLANCK_CONSTANT*SPEED_OF_LIGHT / (samplingPeriod*wavelength);
	// end new

	for (int i = 0; i < process; i++) {

		noiseAmp1 = distribution(generatorAmp1);
		noiseAmp2 = distribution(generatorAmp2);

		/*
		//DIA> debug
		printf("noiseAmp1: %f\n", noiseAmp1);
		printf("noiseAmp2: %f\n", noiseAmp2);
		//END DIA
		*/

		t_complex input1;
		inputSignals[0]->bufferGet(&input1);
		t_complex input2;
		inputSignals[1]->bufferGet(&input2);

		/*
		// Incio de implementação de beat frequency.
		t_real powerSignal1 = gauss[aux]; // Assuming Signal input in PIN1
		t_real powerSignal2 = abs(input1 - input2) / sqrt(2); // Assuming Signal input in PIN2
		*/


		// The 4 factor is compensating the bandpass signal representation amplitude correction.
		t_real power1 = abs(input1)*abs(input1) * 4;
		t_real power2 = abs(input2)*abs(input2) * 4;


		t_real current1 = responsivity*power1;
		t_real current2 = responsivity*power2;
		t_real out = current1 - current2;


		/*
		// Incio de implementação de beat frequency.
		double phaseDifference = 0;
		double arg;
		if (powerSignal1!=0)
		{
			arg = out / (8 * powerSignal1 * powerSignal2);
			if (arg<-1)
			{
				phaseDifference = PI;
			} else if (arg>1) {
				phaseDifference = 0;
			}
			else
			{
				phaseDifference = (acos(arg));
			}
		}
		*/


		if (shotNoise)
		{
			/*
			// [DIA] Debug
			printf("p1: %g\n", power1);
			printf("p2: %g\n", power2);
			// end debug
			*/

			//DIA>

			// Isto está correcto? 
			power1 += sqrt(P)*noiseAmp1*(sqrt(power1) + sqrt(P)*noiseAmp1 / 4);
			power2 += sqrt(P)*noiseAmp2*(sqrt(power2) + sqrt(P)*noiseAmp2 / 4);

			// Será assim?
			//power1 += sqrt(P)*noiseAmp1*(sqrt(power1)*0 + sqrt(P) / 4);
			//power2 += sqrt(P)*noiseAmp2*(sqrt(power2)*0 + sqrt(P) / 4);
			
			//END DIA

			current1 = responsivity*power1;
			current2 = responsivity*power2;

			/*
			//DIA>
			printf("n1: %g\n", sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (samplingPeriod*wavelength))*noiseAmp1*(sqrt(power1) + sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (samplingPeriod*wavelength))*noiseAmp1 / 4));
			printf("samplingPeriod: %g\n", samplingPeriod);
			printf("p1: %g\n", power1);
			printf("p2: %g\n", power2);
			//END DIA
			*/

			out = current1 - current2;

		}


		/*
		// Início de implementação de beat frequency.
		if (frequencyMismatch != 0){
 			out = powerSignal1*powerSignal2*(cos(phaseDifference)*cos(frequencyMismatch*t) - sin(phaseDifference)*sin(frequencyMismatch*t));
			if (1/samplingPeriod < frequencyMismatch/PI )
			{
				cout << "ERRO: photodiode.cpp (Nyquist frequency not respected, aliasing possible)" << "\n";
				return false;
			}
		}
		*/


		outputSignals[0]->bufferPut(out);
		myfile2 << out << "\n";
		t = t + samplingPeriod;
		aux++;
		if (aux==samplesPerSymbol)
		{
			aux = 0;
		}



	}
	return true;
}
