# include <algorithm> // min

# include "netxpto.h"
# include "discrete_to_continuous_time.h"

void DiscreteToContinuousTime::initialize(void) {

	outputSignals[0]->symbolPeriod = (inputSignals[0]->symbolPeriod);
	outputSignals[0]->samplingPeriod = (inputSignals[0]->samplingPeriod) / numberOfSamplesPerSymbol;
	outputSignals[0]->samplesPerSymbol = numberOfSamplesPerSymbol;
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

}

bool DiscreteToContinuousTime::runBlock(void) {

	int length;
	bool alive{ false };

	int ready = inputSignals[0]->ready();
	int space = outputSignals[0]->space();
	
	signal_value_type inSignalType = inputSignals[0]->getValueType();

	if (inSignalType != RealValue) cout << "In signal not a real value!" << endl;

	if (index != 0) {
		length = min(numberOfSamplesPerSymbol - index, space);
		if (length > 0) alive = true;

		switch (inSignalType) {
		case RealValue:
			for (int i = 0; i < length; i++) {
				outputSignals[0]->bufferPut((t_real) 0.0);
				index++;
			}
			index = index % numberOfSamplesPerSymbol;

		//default: cout << "ERRO: discrete_to_continuous_time.cpp - Phase I" << "\n";
		}
		
	};

	if (index != 0) return alive;

	//int length = min((int)ceil((double)space / (double)numberOfSamplesPerSymbol), ready);

	length = min(space, ready*numberOfSamplesPerSymbol);
	if (length <= 0) return alive;

	switch (inSignalType) {
		case RealValue:
			t_real value;
			for (int i = 0; i < length; i++) {
				if (index != 0) {
					outputSignals[0]->bufferPut((t_real) 0.0);
				}
				else {
					(inputSignals[0])->bufferGet(&value);
					outputSignals[0]->bufferPut(value);
				}
				space--;
				index++;
				index = index % numberOfSamplesPerSymbol;
			}
		//default:
			//cout << "ERRO: discrete_to_continuous_time.cpp - Phase II" << "\n";
			return false;
	};
	return alive;
};
