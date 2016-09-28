# include <algorithm>  // min

# include "netxpto.h"
# include "single_photon_source.h"

void SinglePhotonSource::initialize(void) {

	outputSignals[0]->symbolPeriod = inputSignals[0]->symbolPeriod;
	outputSignals[0]->samplingPeriod = inputSignals[0]->samplingPeriod;
	outputSignals[0]->samplesPerSymbol = inputSignals[0]->samplesPerSymbol;
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

}

bool SinglePhotonSource::runBlock(void) {

	int ready = inputSignals[0]->ready();
	int space = outputSignals[0]->space();

	int length = min(ready, space);

	if (length <= 0) return false;

	for (int i = 0; i < length; i++) {
		t_real value;
		t_photon photon;
		inputSignals[0]->bufferGet(&value);
		if (value == 1) {
			photon.probabilityAmplitude = 1;
			photon.polarization = polarization;
			outputSignals[0]->bufferPut(photon);
		}
		else {
			photon.probabilityAmplitude = 0;
			photon.polarization = 0;
			outputSignals[0]->bufferPut(photon);
		}
	}

	return true;

};
