#include <algorithm>
#include <complex>

#include "netxpto.h"
#include "photodiode.h"


void photodiode::initialize(void){

	firstTime = false;

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

	outputSignals[0]->centralWavelength = outputOpticalWavelength;
	outputSignals[0]->centralFrequency = outputOpticalFrequency;

	outputSignals[1]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[1]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[1]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

	outputSignals[1]->centralWavelength = outputOpticalWavelength;
	outputSignals[1]->centralFrequency = outputOpticalFrequency;
}


bool photodiode::runBlock(void){
	int ready = inputSignals[0]->ready();

	int space1 = outputSignals[0]->space();
	int space2 = outputSignals[0]->space();
	int space = min(space1, space2);

	int process = min(ready, space);

	if (process == 0) return false;

	t_real radius = 0.0003; // radius of sensor
	t_real E0 = 8.854187817e-12;
	
	for (int i = 0; i < process; i++) {

		t_complex input1;
		inputSignals[0]->bufferGet(&input1);
		t_complex input2;
		inputSignals[1]->bufferGet(&input2);
		t_real in1r = real(input1);
		t_real in1i = imag(input1);
		t_real in2r = real(input2);
		t_real in2i = imag(input2);


		t_real power1 = 2 * SPEED_OF_LIGHT * PI * radius*radius * E0 * ( in1r * in1r + in1i * in1i ) * 0.25;
		t_real current1 = 1 * power1; // assuming power in wats, need to check if this is correct

		t_real power2 = 2 * SPEED_OF_LIGHT * PI * radius*radius * E0 * ( in2r * in2r + in2i * in2i ) * 0.25;
		t_real current2 = 1 * power2; // assuming power in wats, need to check if this is correct


		outputSignals[0]->bufferPut(current1);
		outputSignals[1]->bufferPut(current2);

	}
	return true;
}