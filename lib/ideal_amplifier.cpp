#include <algorithm>
#include <complex>
#include <random>
#include <fstream>
#include <iostream>

#include "netxpto.h"
#include "ideal_amplifier.h"


void IdealAmplifier::initialize(void){

	firsTime = false;

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());
}


bool IdealAmplifier::runBlock(void){

	ofstream myfile;
	myfile.open("translate.txt", fstream::app);

	int ready = inputSignals[0]->ready();

	int space = outputSignals[0]->space();

	int process = min(ready, space);

	if (process == 0) {
		return false;
		myfile.close();
	}
	for (int i = 0; i < process; i++) {

		t_complex input;
		inputSignals[0]->bufferGet(&input);
		
		myfile << input << "\n";

		t_complex output = input*amplification; 

		outputSignals[0]->bufferPut(output);
	}
	return true;
}