# include <algorithm>
# include <complex>
# include <iostream>
# include <fstream>
# include <random>

# include "netxpto.h"
# include "decoder.h"

using namespace std;

void Decoder::initialize(void) {

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod()/log2(m));
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSymbolPeriod() / log2(m));
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

}

void Decoder::setM(int mValue) {

	m = mValue;

	iqValues.resize(m);
	switch (m) {
	case 4:
		iqValues = { { 1.0, 1.0 },{ -1.0, 1.0 },{ -1.0, -1.0 },{ 1.0, -1.0 } };
	};
};

bool Decoder::runBlock(void) {

	int ready0 = inputSignals[0]->ready();
	int ready1 = inputSignals[1]->ready();
	int ready = min(ready0, ready1);

	int space = outputSignals[0]->space();
	int process = floor(space / log2(m));
	process = min(ready, process);

	if (process == 0) return false;

	t_real in1, in2;
	double d, minimum;

	//Initialize the variable minimum
	
	for (int k = 0; k < process; k++) {
		
		inputSignals[0]->bufferGet(&in1);
		inputSignals[1]->bufferGet(&in2);

		complex<double> s_in(in1, in2);
		minimum = norm(s_in - iqValues[0]);
		int aux{ 0 };
		for (int l = 1; l < m; l++) {
			d = norm(s_in - iqValues[l]);
			if (d < minimum) {
				minimum = d;
				aux = l;
			}
		}
		for (int n = 0; n < log2(m); n++) {
			t_binary s_out = mod(aux, 2);
			outputSignals[0]->bufferPut(s_out);
			aux = div(aux, 2);
		}
	}

	return true;
}