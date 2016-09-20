#include <algorithm>
#include <complex>

#include "netxpto.h"
#include "discretizer.h"


void discretizer::initialize(void){

	firstTime = false;

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
}


bool discretizer::runBlock(void){
	int ready = inputSignals[0]->ready();
	

	int space = outputSignals[0]->space();
	int process = min(ready, space);
	int period = 16;
	int auxint = 15;

	t_real in;
	t_real out;

	if (process == 0) return false;

	

	for (int i = 0; i < ready; i++) {

		
		inputSignals[0]->bufferGet(&in);
		auxint = auxint + 1;

		if (auxint == period)
		{
			auxint = 0;
			out = in;
			outputSignals[0]->bufferPut(out);
		}

	}

	return true;
}