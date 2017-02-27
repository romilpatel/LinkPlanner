# include "netxpto.h"
# include "pulse_shaper_freq.h"

using namespace std;

void raisedCosineTF(vector<t_complex> &transferFunction, int transferFunctionLength, double rollOffFactor, double samplingPeriod, double symbolPeriod);

void PulseShaper::initialize(void) {

	double samplingPeriod = inputSignals[0]->samplingPeriod;
	double symbolPeriod = inputSignals[0]->symbolPeriod;

	transferFunction.resize(transferFunctionLength);

	switch (getFilterType()) {

		case RaisedCosine:
			raisedCosineTF(transferFunction, transferFunctionLength, rollOffFactor, samplingPeriod, symbolPeriod);
			break;
	};

}

void PulseShaper::run(void) {

	outSigTime = ifft(fft(inSigTime)*transferFunction);

};

void raisedCosineTF(vector<t_real> &impulseResponse, int impulseResponseLength, double rollOffFactor, double samplingPeriod, double symbolPeriod) {
	double sinc;
	for (int i = 0; i < impulseResponseLength; i++) {
		t_real t = -impulseResponseLength / 2 * samplingPeriod + i * samplingPeriod;
		if (t != 0) {
			sinc = sin(PI * t / symbolPeriod) / (PI * t / symbolPeriod);
		}
		else {
			sinc = 1;
		}
		impulseResponse[i] = sinc*cos(rollOffFactor*PI*t / symbolPeriod) / (1 - (4.0 * rollOffFactor * rollOffFactor * t * t) / (symbolPeriod * symbolPeriod));
	};
};