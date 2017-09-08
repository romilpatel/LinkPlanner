#include <algorithm>
#include <complex>
#include <chrono>
#include <fstream>

#include "netxpto.h"
#include "photodiode.h"
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> Romil
#include <random>


void Photodiode::initialize(void){
<<<<<<< HEAD
=======


void Photodiode::initialize(void) {
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil

	firstTime = false;

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

}


<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil
bool Photodiode::runBlock(void){

	double samplingPeriod = inputSignals[0]->getSamplingPeriod();

	int samplesPerSymbol = inputSignals[0]->getSamplesPerSymbol();

	int ready1 = inputSignals[0]->ready();
	int ready2 = inputSignals[1]->ready();
	int ready = min(ready1, ready2);
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======

bool Photodiode::runBlock(void) {

	int ready0 = inputSignals[0]->ready();
	int ready1 = inputSignals[1]->ready();
	int ready = min(ready0, ready1);
>>>>>>> AnaLuisa
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil

	int space = outputSignals[0]->space();

	int process = min(ready, space);

	if (process == 0) return false;

<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil
	normal_distribution<double> distribution(0, 1);
	double w1 = inputSignals[0]->getCentralFrequency();
	double w2 = inputSignals[1]->getCentralFrequency();
	frequencyMismatch = abs(w1 - w2);
	double noiseAmp1;
	double noiseAmp2;

	double wavelength = inputSignals[0]->getCentralWavelength();

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();


	
	generatorAmp1.seed(seed);
	generatorAmp2.seed(seed);

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

	for (int i = 0; i < process; i++) {

		noiseAmp1 = distribution(generatorAmp1);
		noiseAmp2 = distribution(generatorAmp2);

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> Romil

		t_complex input1;
		inputSignals[0]->bufferGet(&input1);
		t_complex input2;
		inputSignals[1]->bufferGet(&input2);

<<<<<<< HEAD
=======
=======
	/*t_real radius = 0.0003; // radius of sensor
	t_real E0 = 8.854187817e-12;
	t_real n = 1.1;*/

	t_complex inputSignal1;
	t_complex inputSignal2;
>>>>>>> AnaLuisa

	for (int i = 0; i < process; i++) {

<<<<<<< HEAD
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil
		t_real powerSignal1 = gauss[aux]; // Assuming Signal input in PIN1
		t_real powerSignal2 = abs(input1 - input2) / sqrt(2); // Assuming Signal input in PIN2		

		t_real power1 = abs(input1)*abs(input1) * 4;
		t_real power2 = abs(input2)*abs(input2) * 4;


		t_real current1 = responsivity*power1;
		t_real current2 = responsivity*power2;
		t_real out = current1 - current2;
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


		if (shotNoise)
		{
			power1 = power1 + sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (samplingPeriod*wavelength))*noiseAmp1*(sqrt(power1) + sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (samplingPeriod*wavelength))*noiseAmp1 / 4);
			power2 = power2 + sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (samplingPeriod*wavelength))*noiseAmp2*(sqrt(power2) + sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (samplingPeriod*wavelength))*noiseAmp2 / 4);
			current1 = responsivity*power1;
			current2 = responsivity*power2;
			t_real out = current1 - current2;
		}

		if (frequencyMismatch != 0){
 			out = powerSignal1*powerSignal2*(cos(phaseDifference)*cos(frequencyMismatch*t) - sin(phaseDifference)*sin(frequencyMismatch*t));
			if (1/samplingPeriod < frequencyMismatch/PI )
			{
				cout << "ERRO: photodiode.cpp (Nyquist frequency not respected, aliasing possible)" << "\n";
				return false;
			}
		}

		outputSignals[0]->bufferPut(out);
		t = t + samplingPeriod;
		aux++;
		if (aux==samplesPerSymbol)
		{
			aux = 0;
		}



<<<<<<< HEAD
<<<<<<< HEAD
	}
	return true;
}
=======
=======
			inputSignals[0]->bufferGet(&inputSignal1);
			inputSignals[1]->bufferGet(&inputSignal2);

			t_real power1 = abs(inputSignal1)*abs(inputSignal1)*2; 
			t_real current1 = responsivity * power1;

			t_real power2 = abs(inputSignal2)*abs(inputSignal2)*2;
			t_real current2 = responsivity * power2;

			t_real outputSignal = current1 - current2;

			outputSignals[0]->bufferPut(outputSignal);

		
>>>>>>> AnaLuisa
	}
	return true;
}
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
	}
	return true;
}
>>>>>>> Romil
