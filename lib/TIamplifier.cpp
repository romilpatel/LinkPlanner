#include <algorithm>
#include <complex>
#include <random>
#include <fstream>
#include <iostream>

#include "netxpto.h"
#include "TIamplifier.h"


void TIAmplifier::initialize(void){

	firsTime = false;

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());
}


bool TIAmplifier::runBlock(void){

	normal_distribution<double> distribution( 0, noiseamp);

	int ready = inputSignals[0]->ready();

	int space = outputSignals[0]->space();

	int process = min(ready, space);

	if (process == 0) return false;

	double noise = 0;

	for (int i = 0; i < process; i++) {

		t_real input;
		inputSignals[0]->bufferGet(&input);
		
		noise = distribution(generator);
		
		t_real output = input*amplification +noise; // assuming current in amps

		outputSignals[0]->bufferPut(output);
	}
	return true;
}