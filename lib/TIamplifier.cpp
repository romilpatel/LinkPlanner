#include <algorithm>
#include <complex>

#include "..\include\netxpto.h"
#include "..\include\TIamplifier.h"


TIamplifier::TIamplifier(vector <Signal *> &InputSig, vector <Signal *> &OutputSig){

	numberOfInputSignals = InputSig.size();
	numberOfOutputSignals = OutputSig.size();

	inputSignals = InputSig;
	outputSignals = OutputSig;

	outputSignals[0]->symbolPeriod = inputSignals[0]->symbolPeriod;
	outputSignals[0]->samplingPeriod = inputSignals[0]->samplingPeriod;
}


bool TIamplifier::runBlock(void){
	int ready = inputSignals[0]->ready();

	int space0 = outputSignals[0]->space();

	int process = min(ready, space0);

	if (process == 0) return false;
	
	for (int i = 0; i < process; i++) {

		t_real signalValue;
		inputSignals[0]->bufferGet(&signalValue);
		t_real out = signalValue*10000000; // assuming current in amps

		outputSignals[0]->bufferPut(out);
	}
	return true;
}