#include <algorithm>
#include <complex>
#include <iostream>
#include <fstream>

#include "netxpto.h"
#include "testblock.h"


testblock::testblock(vector <Signal *> &InputSig, vector <Signal *> &OutputSig){

	numberOfInputSignals = InputSig.size();
	numberOfOutputSignals = OutputSig.size();

	inputSignals = InputSig;
	outputSignals = OutputSig;

	outputSignals[0]->symbolPeriod = inputSignals[0]->symbolPeriod;;
	outputSignals[0]->samplingPeriod = inputSignals[0]->samplingPeriod;
}


bool testblock::runBlock(void){
	int ready = inputSignals[0]->ready();

	int space = outputSignals[0]->space();

	int process = min(ready, space);

	if (process == 0) return false;

	for (int i = 0; i < process; i++) {

		t_complex_xy signalValue;
		inputSignals[0]->bufferGet(&signalValue);



		
		cout << "XVALUE is " << signalValue.x << "\n";
		cout << "YValue is " << signalValue.y << "\n";


		outputSignals[0]->bufferPut(&signalValue);

	}
	return true;
	
}