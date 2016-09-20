#include <algorithm>
#include <complex>

#include "..\include\netxpto.h"
#include "..\include\subtractor.h"


void subtractor::initialize(void){

	firstTime = false;

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());
}


bool subtractor::runBlock(void){
	int ready1 = inputSignals[0]->ready();
	int ready2 = inputSignals[1]->ready();
	int ready = min(ready1, ready2);

	int space0 = outputSignals[0]->space();

	int process = min(ready, space0);

	if (process == 0) return false;
	
	for (int i = 0; i < process; i++) {

		t_real in1;
		inputSignals[0]->bufferGet(&in1);
		t_real in2;
		inputSignals[1]->bufferGet(&in2);

		t_real out = in1 - in2;

		outputSignals[0]->bufferPut(out);
	}
	return true;
}
