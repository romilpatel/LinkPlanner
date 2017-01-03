#include <algorithm>
#include <complex>

#include "netxpto.h"
#include "subtractor.h"


void Subtractor::initialize(void) {

	firstTime = false;

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

	outputSignals[1]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[1]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[1]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());
}


bool Subtractor::runBlock(void) {

	int ready1 = inputSignals[0]->ready();
	int ready2 = inputSignals[1]->ready();
	int ready = min(ready1, ready2);

	int space0 = outputSignals[0]->space();

	int process = min(ready, space0);

	if (process == 0) return false;

	for (int i = 0 ; i < process ; i++) {

		t_real in1;
		inputSignals[0]->bufferGet(&in1);
		t_real in2;
		inputSignals[1]->bufferGet(&in2);

		t_real in3;
		inputSignals[2]->bufferGet(&in3);
		t_real in4;
		inputSignals[4]->bufferGet(&in4);

		t_real out1 = in1 - in2;
		t_real out2 = in3 - in4;


		outputSignals[0]->bufferPut(out1);
		outputSignals[1]->bufferPut(out2);

	}
	return true;
}
