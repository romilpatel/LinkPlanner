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

  normal_distribution<double> distribution(0, 1);
	t_real dt = inputSignals[0]->getSamplingPeriod();
	t_real wvlgth = inputSignals[0]->getCentralWavelength();
	t_real noisesignal;
	t_real noiselo;
	int space0 = outputSignals[0]->space();
	int space1 = outputSignals[1]->space();
	int space = min(space0, space1);

	int process = min(ready, space);

	if (process == 0) return false;

	t_real real = cos(LocalOscillatorPhase);
	t_real imag = sin(LocalOscillatorPhase);
	t_complex lo(real, imag);
	t_real powerlo = outputOpticalPower;

	for (int i = 0; i < process; i++) {


		noisesignal = distribution(generator1);
		noiselo = distribution(generator2);

		t_complex signalValue;
		inputSignals[0]->bufferGet(&signalValue);

		t_complex loout;
		t_complex signalout;

        if (shotnoise) {
            t_real powerlooutsqrted = sqrt(powerlo) + sqrt(h*SPEED_OF_LIGHT / (dt * wvlgth))*noiselo*1/2;
            loout = .5*powerlooutsqrted*lo;
            
            t_real powersignal = 4 * norm(signalValue);
            t_real phase = arg(signalValue);
            t_complex signal(cos(phase), sin(phase));
            t_real powersignaloutsqrted = sqrt(powersignal) + sqrt(h*SPEED_OF_LIGHT / (dt*wvlgth))*noisesignal*1 / 2;
            signalout = .5*powersignaloutsqrted*signal;
        } else
        {
			loout = lo;
			signalout = signalValue;
        }
		

        
		outputSignals[0]->bufferPut(signalout);
		outputSignals[1]->bufferPut(loout);

	}
	return true;
}
