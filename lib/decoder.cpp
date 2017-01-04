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

	iqValues.resize(m);
	switch (m) {
	case 4:
		iqValues = { { 1.0, 1.0 },{ -1.0, 1.0 },{ -1.0, -1.0 },{ 1.0, -1.0 } };
		iqBinaryValues = { { 00 },{ 01 }, { 10 }, { 11 } };
	};
};

bool Decoder::runBlock(void) {

	int ready0 = inputSignals[0]->ready();
	int ready1 = inputSignals[1]->ready();
	int ready = min(ready0, ready1);

	int space = outputSignals[0]->space();

	int process = min(ready, space);

	if (process == 0) return false;

	t_real in1, in2;
	t_real s_out;
	double d, minimum;

	//Initialize the variable minimum

	inputSignals[0]->bufferGet(&in1);
	inputSignals[1]->bufferGet(&in2);

	complex<double> s_in(in1, in2);

	minimum = norm(s_in - iqValues[0]);

	for (int k = 0; k < process; k++) {

		inputSignals[0]->bufferGet(&in1);
		inputSignals[1]->bufferGet(&in2);

		complex<double> s_in(in1, in2);

		for (int j = 0; j < m; j++) {
		
			d = norm(s_in - iqValues[j]);

			if (d < minimum) {

				minimum = d;
				s_out = iqBinaryValues[j];

			}

		}

		outputSignals[0]->bufferPut(s_out);

	}

	return true;
}