#include <algorithm>
#include <complex>

#include "..\include\netxpto.h"
#include "..\include\subtractor.h"


subtractor::subtractor(vector <Signal *> &InputSig, vector <Signal *> &OutputSig){

	numberOfInputSignals = InputSig.size();
	numberOfOutputSignals = OutputSig.size();

	inputSignals = InputSig;
	outputSignals = OutputSig;

	outputSignals[0]->symbolPeriod = inputSignals[0]->symbolPeriod;
	outputSignals[0]->samplingPeriod = inputSignals[0]->samplingPeriod;
}


bool subtractor::runBlock(void){
	int ready0 = inputSignals[0]->ready();
	int ready = ready0;

	int space0 = outputSignals[0]->space();

	int process = min(ready, space0);

	if (process == 0) return false;
	
	for (int i = 0; i < process; i++) {

		t_real x1;
		inputSignals[0]->bufferGet(&x1);
		t_real x2;
		inputSignals[1]->bufferGet(&x2);

		t_real out = x1 + x2;

		outputSignals[0]->bufferPut(out);
	}
	return true;
}
