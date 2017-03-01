#include <algorithm>
#include <complex>

#include "netxpto.h"
#include "add.h"


void Add::initialize(void){

	firstTime = false;

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());
}


bool Add::runBlock(void){
	int ready1 = inputSignals[0]->ready();
	int ready2 = inputSignals[1]->ready();
	int ready = min(ready1, ready2);

	int space0 = outputSignals[0]->space();

	int process = min(ready, space0);

	if (process == 0) return false;
	
	for (int i = 0; i < process; i++) {

		t_complex in1;
		inputSignals[0]->bufferGet(&in1);
		t_complex in2(0, 0);
		t_complex noise;
		inputSignals[1]->bufferGet(&noise);
		if (opticalNoise)
		{
			in2 = in2 + noise;
		}


		t_complex out = in1 + in2;

		outputSignals[0]->bufferPut(out);
	}
	return true;
}
