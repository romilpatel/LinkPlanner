#include <algorithm>
#include <complex>

#include "netxpto.h"
#include "BalancedBeamsplitter.h"


BalancedBeamsplitter::BalancedBeamsplitter(vector <Signal *> &InputSig, vector <Signal *> &OutputSig){

	numberOfInputSignals = InputSig.size();
	numberOfOutputSignals = OutputSig.size();

	inputSignals = InputSig;
	outputSignals = OutputSig;

	outputSignals[0]->symbolPeriod = inputSignals[0]->symbolPeriod;
	outputSignals[0]->samplingPeriod = inputSignals[0]->samplingPeriod;

	outputSignals[1]->symbolPeriod = inputSignals[0]->symbolPeriod;
	outputSignals[1]->samplingPeriod = inputSignals[0]->samplingPeriod;
}


bool BalancedBeamsplitter::runBlock(void){
	int ready0 = inputSignals[0]->ready();
	int ready1 = inputSignals[1]->ready();
	int ready = min(ready0, ready1);

	int space0 = outputSignals[0]->space();
	int space1 = outputSignals[1]->space();

	int process = min(ready, space0);

	if (process == 0) return false;
	
	for (int i = 0; i < process; i++) {

		t_complex x1;
		inputSignals[0]->bufferGet(&x1);
		t_complex x2;
		inputSignals[1]->bufferGet(&x2);

		
		t_real t = 1;
		complex<t_real> imaginary(0,t);

		t_complex x4 = div*(x1 + x2);
		t_complex x3 = div*(x1 - x2);

		
		/*
		t_complex x4 = div*(x1-x2*imaginary);
		t_complex x3 = div*(-x1*imaginary + x2);
		*/
		outputSignals[0]->bufferPut(x3);
		outputSignals[1]->bufferPut(x4);
	}
	return true;
}
