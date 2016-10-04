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

	outputSignals[0]->centralWavelength = outputOpticalWavelength;
	outputSignals[0]->centralFrequency = outputOpticalFrequency;

	outputSignals[1]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[1]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[1]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

	outputSignals[1]->centralWavelength = outputOpticalWavelength;
	outputSignals[1]->centralFrequency = outputOpticalFrequency;
}


bool testblock::runBlock(void){

	default_random_engine generator;
	normal_distribution<t_real> distribution(0, 1.1e-3);

	int ready = inputSignals[0]->ready();
	int space = outputSignals[0]->space();

	int process = min(ready, space);

	if (process == 0) return false;

	t_complex_xy signalValue;
	t_complex signalValuex;
	t_complex lo( 1, 0);
	lo = .5*sqrt(1e-3*pow(10, -25 / 10))*lo*.9;

	for (int i = 0; i < process; i++) {
		inputSignals[0]->bufferGet(&signalValue);
		signalValuex = signalValue.x;
		
		outputSignals[0]->bufferPut(signalValuex);
		outputSignals[1]->bufferPut(lo);

	}
	return true;
	
}