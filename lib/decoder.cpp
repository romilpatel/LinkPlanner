# include <algorithm>
# include <complex>
# include <iostream>
# include <fstream>
# include <random>

# include "netxpto.h"
# include "decoder.h"

using namespace std;

void Decoder::initialize(void) {

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

	outputSignals[0]->centralWavelength = outputOpticalWavelength;
	outputSignals[0]->centralFrequency = outputOpticalFrequency;

	setM(m);
}

void Decoder::setM(int mValue) {
	m = mValue;

	iqBinaryValues.resize(m);
	switch (m) {
	case 4:
		iqBinaryValues = { { 00 },{ 01 },{ 10 },{ 11 } };
	};
};

bool Decoder::runBlock(void) {

	int ready0 = inputSignals[0]->ready();
	int ready1 = inputSignals[1]->ready();
	int ready = min(ready0, ready1);

	int space = outputSignals[0]->space();

	int process = min(ready, space);

	if (process == 0) return false;

	t_real input1, input2;

	for (int i = 0; i < process; i++) {

		inputSignals[0]->bufferGet(&input1);
		inputSignals[1]->bufferGet(&input2);

		if (input1>0 && input2>0) {

			outputSignals[0]->bufferPut(iqBinaryValues[0]);
		
		}
		else if (input1<0 && input2>0) {
		
			outputSignals[0]->bufferPut(iqBinaryValues[1]);
		
		}
		else if (input1<0 && input2<0) {

			outputSignals[0]->bufferPut(iqBinaryValues[2]);

		}
		else if (input1>0 && input2<0) {

			outputSignals[0]->bufferPut(iqBinaryValues[3]);

		}
	}

	return true;
}