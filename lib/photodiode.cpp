#include <algorithm>
#include <complex>

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
	double dt = 2.33e-8;//inputSignals[0]->getSamplingPeriod();
	double noise1I;
	double noise1Q;
	double noise2I;
	double noise2Q;

	double wavelength = outputOpticalWavelength;


	
	for (int i = 0; i < process; i++) {

		noise1I = distribution(generator1I);
		noise2I = distribution(generator2I);

		noise1Q = distribution(generator1Q);
		noise2Q = distribution(generator1Q);

		t_complex input1;
		inputSignals[0]->bufferGet(&input1);
		t_complex input2;
		inputSignals[1]->bufferGet(&input2);

		t_real input1I = real(input1);
		t_real input1Q = imag(input1);
		t_real input2I = real(input2);
		t_real input2Q = imag(input2);

		t_real power1I = input1I*input1I * 4;
		t_real power1Q = input1Q*input1Q * 4;

		t_real power2I = input2I*input2I * 4;
		t_real power2Q = input2Q*input2Q * 4;

		t_real current1;
		t_real current2;

		if (shotNoise)
		{
			power1I = power1I + sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (dt*wavelength))*noise1I*(sqrt(power1I) + sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (dt*wavelength))*noise1I / 4);
			power1Q = power1Q + sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (dt*wavelength))*noise1Q*(sqrt(power1Q) + sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (dt*wavelength))*noise1Q / 4);
			
			power2I = power2I + sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (dt*wavelength))*noise2I*(sqrt(power2I) + sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (dt*wavelength))*noise2I / 4);
			power2Q = power2Q + sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (dt*wavelength))*noise2Q*(sqrt(power2Q) + sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (dt*wavelength))*noise2Q / 4);
		}

		current1 = responsivity*(power1I + power1Q);
		current2 = responsivity*(power2I + power1Q);
		t_real out = current1 - current2;

		outputSignals[0]->bufferPut(out);
	}
	return true;
}
