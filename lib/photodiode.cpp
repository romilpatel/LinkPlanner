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
	double dt = inputSignals[0]->getSamplingPeriod();
	double w1 = inputSignals[0]->getCentralFrequency();
	double w2 = inputSignals[1]->getCentralFrequency();
	w1 = w1 + 1;
	double wb = abs(w2 - w1);
	double noiseAmp1;
	double noiseAmp2;

	double wavelength = inputSignals[0]->getCentralWavelength();

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();


	
	generatorAmp1.seed(seed);
	generatorAmp2.seed(seed);

	double pulsewidth = 5e-10;
	double amp=.5*sqrt(6.4078e-13*5);
	int impulseResponseLength = 2560;

	vector<t_real> gauss;
	gauss.resize(impulseResponseLength);

	for (int i = 0; i < impulseResponseLength; i++)
	{
		t_real time = -impulseResponseLength / 2 * dt + i*dt;
		gauss[i] = amp*exp(-time*time / (pulsewidth*pulsewidth / 36));
	}


	double t = 0;
	for (int i = 0; i < process; i++) {

		noiseAmp1 = distribution(generatorAmp1);
		noiseAmp2 = distribution(generatorAmp2);


		t_complex input1;
		inputSignals[0]->bufferGet(&input1);
		t_complex input2;
		inputSignals[1]->bufferGet(&input2);

		double powerSignal1 = abs(input1 + input2) / sqrt(2);
		double powerSignal2 = abs(input1 - input2) / sqrt(2);


		

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
			power1 = power1 + sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (dt*wavelength))*noiseAmp1*(sqrt(power1) + sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (dt*wavelength))*noiseAmp1 / 4);
			power2 = power2 + sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (dt*wavelength))*noiseAmp2*(sqrt(power2) + sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (dt*wavelength))*noiseAmp2 / 4);
			current1 = responsivity*power1;
			current2 = responsivity*power2;
			t_real out = current1 - current2;
		}

		if (frequencyMismatch != 0){
			out = powerSignal1*powerSignal2*(cos(phaseDifference)*cos(frequencyMismatch*t) - sin(phaseDifference)*sin(frequencyMismatch*t));
			if (1/dt < frequencyMismatch/PI )
			{
				cout << "Nyquist frequency not respected, aliasing possible" << "\n";
				return false;
			}
		}

		outputSignals[0]->bufferPut(out);
		myfile2 << out << "\n";
		t = t + dt;
		j++;
		if (j==impulseResponseLength)
		{
			j = 0;
		}
	}
	return true;
}
