#include <algorithm>
#include <complex>
#include <iostream>

#include "netxpto.h"
#include "sampler.h"


void Sampler::initialize(void){

	firstTime = false;

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSymbolPeriod());
}


bool Sampler::runBlock(void){

	int ready = inputSignals[0]->ready();
	
	if (samplesToSkip > 0) {
		int process = min(ready, samplesToSkip);

		for (int k = 0; k < process; k++) {
			t_real in;
			inputSignals[0]->bufferGet(&in);
		}

		samplesToSkip = samplesToSkip - process;

		ready = inputSignals[0]->ready();

	}

	int space = outputSignals[0]->space();
	int process = min(ready, space);
	
	
	if (process == 0) return false;

	double sPerSymbol = inputSignals[0]->getSamplesPerSymbol();

	for (int k = 0; k < process; k++) {
		t_real in;
		inputSignals[0]->bufferGet(&in);
		if (k % (int) sPerSymbol == 0) {
			outputSignals[0]->bufferPut((t_real) in);
		}
	}

	return true;
}