#include <algorithm>
#include <complex>
#include <iostream>
#include <fstream>
#include <random>

#include "netxpto.h"
#include "testblock.h"


void testblock::initialize(void){

	firstTime = false;

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());
}


bool testblock::runBlock(void){

	default_random_engine generator;
	normal_distribution<t_real> distribution(0, 1.1e-3);

	int ready = inputSignals[0]->ready();
	int space = outputSignals[0]->space();

	int process = min(ready, space);

	if (process == 0) return false;

	for (int i = 0; i < process; i++) {
		t_real signalValue;
		inputSignals[0]->bufferGet(&signalValue);

		

		t_real noise = distribution(generator);

		t_real SignalValue = signalValue * 1e6 +noise;
		
		/*
		cout << "noise is " << noise << "\n";
		cout << "value is " << signalValue << "\n";
		cout << "out is " <<  SignalValue << "\n";
		*/

		outputSignals[0]->bufferPut(SignalValue);

	}
	return true;
	
}