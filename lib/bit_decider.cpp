#include <algorithm>
#include <complex>

#include "netxpto.h"
#include "bit_decider.h"


void BitDecider::initialize(void){

	firstTime = false;

	outputSignals[0]->symbolPeriod=bitPeriod;
	outputSignals[0]->samplingPeriod = outputSignals[0]->symbolPeriod;
//	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());
}


bool BitDecider::runBlock(void){
	int ready = inputSignals[0]->ready();
	int space = outputSignals[0]->space();



	int process = min(ready, space);

	if (process == 0) return false;

	for (int i = 0; i < ready; i++) {

		t_real signalValue;
		inputSignals[0]->bufferGet(&signalValue);
		if (signalValue>posreferencevalue)
		{
			outputSignals[0]->bufferPut((t_binary) 0);
		}
		else if (signalValue<negreferencevalue)
		{
			outputSignals[0]->bufferPut((t_binary) 1);
		}
		else
		{
			// do nothing
		}



	}
	return true;
	
}