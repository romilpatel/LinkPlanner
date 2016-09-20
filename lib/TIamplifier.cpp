#include <algorithm>
#include <complex>

#include "netxpto.h"
#include "TIamplifier.h"


void TIamplifier::initialize(void){

	firsTime = false;

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());
}


bool TIamplifier::runBlock(void){
	int ready = inputSignals[0]->ready();

	int space = outputSignals[0]->space();

	int process = min(ready, space);

	if (process == 0) return false;
	
	for (int i = 0; i < process; i++) {

		t_real input;
		inputSignals[0]->bufferGet(&input);
		t_real output = input*10000000; // assuming current in amps

		outputSignals[0]->bufferPut(output);
	}
	return true;
}