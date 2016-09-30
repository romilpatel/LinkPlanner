#include <algorithm>
#include <complex>
#include <iostream>
#include <fstream>

#include "netxpto.h"
#include "local_oscillator.h"

using namespace std;

void LocalOscillator::initialize(void){
	
	firstTime = false;

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

	outputSignals[0]->centralWavelength = outputOpticalWavelength;
	outputSignals[0]->centralFrequency = outputOpticalFrequency;
}


bool LocalOscillator::runBlock(void){
	int ready = inputSignals[0]->ready();
	int space = outputSignals[0]->space();

	int process = min(ready, space);

	if (process == 0) return false;

	for (int i = 0; i < process; i++) {

		t_complex_xy signalValue;
		inputSignals[0]->bufferGet(&signalValue);
		t_complex lo( 1, 0);
		lo = .5*sqrt(1e-3*pow(10,-25/10))*lo*.9;
		t_complex_xy output = { signalValue.x, lo };
		outputSignals[0]->bufferPut(output);
	}
	return true;
}