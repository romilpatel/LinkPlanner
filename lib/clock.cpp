# include "netxpto.h"
# include "clock.h"

using namespace std;

void Clock::initialize(void) {

	outputSignals[0]->setSamplingPeriod(samplingPeriod);
	outputSignals[0]->setCentralWavelength(wavelength);
	outputSignals[0]->setCentralFrequency(frequency);

};

bool Clock::runBlock(void) {

	int space = outputSignals[0]->space();

	if (space == 0) return false;

	int sPerSymbol = 16;

	for (int k = 0; k < space; k++) {
		if (k % sPerSymbol == 0) {
			outputSignals[0]->bufferPut((t_real) 1.0);
		}
		else {
			outputSignals[0]->bufferPut((t_real) 0.0);
		}
	}

	return true;
};