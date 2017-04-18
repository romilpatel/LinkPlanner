#include <algorithm>
#include <complex>
#include <chrono>

#include "netxpto.h"
#include "photodiode.h"
#include <random>


void Photodiode::initialize(void){

	firstTime = false;

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

	outputSignals[0]->centralWavelength = outputOpticalWavelength;
	outputSignals[0]->centralFrequency = outputOpticalFrequency;

}


bool Photodiode::runBlock(void){
	int ready1 = inputSignals[0]->ready();
	int ready2 = inputSignals[1]->ready();
	int ready = min(ready1, ready2);

	int space = outputSignals[0]->space();

	int process = min(ready, space);

	if (process == 0) return false;

	normal_distribution<double> distribution(0, 1);
	double dt = inputSignals[0]->getSamplingPeriod();
	double noiseAmp1;
	double noiseAmp2;

	double wavelength = outputOpticalWavelength;

	unsigned seed = chrono::system_clock::now().time_since_epoch().count();


	
	generatorAmp1.seed(seed);
	generatorAmp2.seed(seed);

	for (int i = 0; i < process; i++) {

		noiseAmp1 = distribution(generatorAmp1);
		noiseAmp2 = distribution(generatorAmp2);

		t_complex input1;
		inputSignals[0]->bufferGet(&input1);
		t_complex input2;
		inputSignals[1]->bufferGet(&input2);

		t_real power1 = abs(input1)*abs(input1) * 4;
		t_real power2 = abs(input2)*abs(input2) * 4;


		t_real current1;
		t_real current2;

		if (shotNoise)
		{
			power1 = power1 + sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (dt*wavelength))*noiseAmp1*(sqrt(power1) + sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (dt*wavelength))*noiseAmp1 / 4);
			power2 = power2 + sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (dt*wavelength))*noiseAmp2*(sqrt(power2) + sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (dt*wavelength))*noiseAmp2 / 4);
			
		}

		current1 = responsivity*power1;
		current2 = responsivity*power2;
		t_real out = current1 - current2;

		outputSignals[0]->bufferPut(out);
	}
	return true;
}
