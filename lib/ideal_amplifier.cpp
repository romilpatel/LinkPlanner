# include "netxpto.h"
# include "ideal_amplifier.h"

# include <algorithm.h> // min

using namespace std;

void IqModulator::initialize(void) {

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());
	outputSignals[0]->centralWavelength(inputSignals[0]->centralWavelength);
	outputSignals[0]->centralFrequency(inputSignals[0]->centralFrequency);

}

bool IqModulator::runBlock(void) {
	
	int ready = inputSignals[0]->ready();
	int space = outputSignals[0]->space();

	int process = min(ready, space);

	if (process == 0) return false;

	switch (inputSignals[0]->type) {
		case t_complex:
			t_complex in;
			for (int k = 0; k < process; k++) {
				inputSignals[0]->bufferGet(&in);
				outputSignals[0]->bufferPut(gain*in);
			}
			break;
	}
	return true;
}
