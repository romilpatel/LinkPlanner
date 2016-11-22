#include <algorithm>
#include <complex>
#include <iostream>
#include <fstream>
#include <random>

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

/*  normal_distribution<double> distribution(0, 1);
	t_real dt = inputSignals[0]->getSamplingPeriod();
	t_real noisesignal;
	t_real noiselo;
*/	int space0 = outputSignals[0]->space();
	int space1 = outputSignals[1]->space();
	int space = min(space0, space1);

	int process = min(ready, space);

	if (process == 0) return false;

	t_complex signalValue; 
	t_real real = cos(LocalOscillatorPhase);
	t_real imag = sin(LocalOscillatorPhase);
	t_complex lo(real, imag);
	lo = .5*sqrt(outputOpticalPower)*lo;
	//t_real powerlo = abs(lo)*abs(lo) * 2;

	for (int i = 0; i < process; i++) {

		//noisesignal = distribution(generator1);
		//noiselo = distribution(generator2);

		inputSignals[0]->bufferGet(&signalValue);

		//t_real powerloout = powerlo + sqrt(h*SPEED_OF_LIGHT / dt)*noiselo*(sqrt(powerlo) + 1 / 2);
		//t_complex loout = .5*sqrt(powerloout)*lo;

		//t_real powersignal = abs(signalValue)*abs(signalValue) * 2;
		//t_real powersignalout = powersignal + sqrt(h*SPEED_OF_LIGHT / dt)*noiselo*(sqrt(powersignal) + 1 / 2);

		outputSignals[0]->bufferPut(signalValue);
		outputSignals[1]->bufferPut(lo);

	}
	return true;
}