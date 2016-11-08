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

	outputSignals[1]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[1]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[1]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

	outputSignals[1]->centralWavelength = outputOpticalWavelength;
	outputSignals[1]->centralFrequency = outputOpticalFrequency;

}


bool LocalOscillator::runBlock(void){
	int ready = inputSignals[0]->ready();
	
	int space0 = outputSignals[0]->space();
	int space1 = outputSignals[1]->space();
	int space = min(space0, space1);

	int process = min(ready, space);

	if (process == 0) return false;

	t_complex signalValue; 
	t_real real = cos(LocalOscillatorPhase);
	t_real imag = sin(LocalOscillatorPhase);
	t_complex lo(real, imag);
	lo = .5*sqrt(outputOpticalPower)*lo;


	for (int i = 0; i < process; i++) {

		inputSignals[0]->bufferGet(&signalValue);

		outputSignals[0]->bufferPut(signalValue);
		outputSignals[1]->bufferPut(lo);

	}
	return true;
}