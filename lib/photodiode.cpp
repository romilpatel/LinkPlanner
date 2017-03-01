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
	int ready = inputSignals[0]->ready();

	normal_distribution<double> distribution(0, 1);
	double dt = 1.28e-8; //inputSignals[0]->getSamplingPeriod();
	double noise1;
	double noise2;

	double wavelength = outputOpticalWavelength;

	int space1 = outputSignals[0]->space();
	int space2 = outputSignals[0]->space();
	int space = min(space1, space2);

	int process = min(ready, space);

	if (process == 0) return false;

	t_real radius = 0.0003; // radius of sensor
	t_real E0 = 8.854187817e-12;
	t_real n = 1.1;
	
	for (int i = 0; i < process; i++) {

		noise1 = distribution(generator1);
		noise2 = distribution(generator2);

		t_complex input1;
		inputSignals[0]->bufferGet(&input1);
		t_complex input2;
		inputSignals[1]->bufferGet(&input2);



		t_real power1 = abs(input1)*abs(input1) * 4;
		t_real power2 = abs(input2)*abs(input2) * 4;
		
		t_real current1 = responsivity * (power1);// assuming power in wats, need to check if this is correct
		t_real current2 = responsivity * (power2);// assuming power in wats, need to check if this is correct

		if (shotNoise)
		{
			current1 = current1 + responsivity * (sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (dt*wavelength))*noise1*(sqrt(power1) + sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (dt*wavelength)) * noise1 / 4));
			current2 = current2 + responsivity * (sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (dt*wavelength))*noise2*(sqrt(power2) + sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (dt*wavelength)) * noise2 / 4));
		}
		
		t_real out = current1 - current2;	

		outputSignals[0]->bufferPut(out);
	}
	return true;
}
