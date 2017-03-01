#include <algorithm>
#include <complex>
#include <random>
#include <fstream>
#include <iostream>

#include "netxpto.h"
#include "ti_amplifier.h"


void TIAmplifier::initialize(void){

	firsTime = false;

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());
}


bool TIAmplifier::runBlock(void){

	ofstream translate;
	translate.open("translate.txt", fstream::app);

	normal_distribution<double> distribution(0, 1);

	int ready = inputSignals[0]->ready();

	int space = outputSignals[0]->space();

	int process = min(ready, space);

	if (process == 0) {
		translate.close();
		return false;
	}
	double noise = 0;

	for (int i = 0; i < process; i++) {

		t_real input;
		inputSignals[0]->bufferGet(&input);
		
		noise = distribution(generator);
		
		t_real output = input*gain; // assuming current in amps

		if (electricalNoiseSpectralDensity!=0)
		{
			output = output + noise*electricalNoiseSpectralDensity;
		}

		translate << output << "\n";


		outputSignals[0]->bufferPut(output);
	}
	return true;
}