# include "netxpto.h"
# include "RF_Oscillator.h"

# include <algorithm>
# include <complex>
# include <iostream>
# include <fstream>
# include <random>

using namespace std;


void RfOscillator::initialize(void) {
	outputSignals[0]->setSamplingPeriod(samplingPeriod);
}


bool RfOscillator::runBlock(void) {

	int process = outputSignals[0]->space();

	if (process == 0) return false;

	double dt = outputSignals[0]->getSamplingPeriod();

	for (int i = 0; i < process; i++) {
		phase = phase + 2*PI*rfFrequency * dt;
		t_real out = .5*sqrt(rfAmplitude)*cos(phase);
		outputSignals[0]->bufferPut((t_real) out);
	}

	return true;
}