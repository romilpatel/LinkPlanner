# include "netxpto.h"
# include "pulse_shaper_freq.h"

using namespace std;

void raisedCosineTF(vector<t_complex> &transferFunction, int transferFunctionLength, double rollOffFactor, double samplingPeriod, double symbolPeriod);

void FD_PulseShaper::initialize(void) {

	double samplingPeriod = inputSignals[0]->samplingPeriod;
	double symbolPeriod = inputSignals[0]->symbolPeriod;

	transferFunction.resize(transferFunctionLength);

	switch (getFilterType()) {

		case RaisedCosine:
			raisedCosineTF(transferFunction, transferFunctionLength, rollOffFactor, samplingPeriod, symbolPeriod);
			break;
	};

}

void FD_PulseShaper::run(void) {};

void raisedCosineTF(vector<t_complex> &transferFunction, int transferFunctionLength, double rollOffFactor, double samplingPeriod, double symbolPeriod) {

	double cond1_if = (1 - rollOffFactor) / (2 * symbolPeriod);
	double cond2_if = (1 + rollOffFactor) / (2 * symbolPeriod);

	t_complex transferFunction_normFactor(0);
	vector<t_real> F(transferFunctionLength, 0);

	for (int i = 0; i < transferFunctionLength; i++) {
		F.at(i) = -(1 / (samplingPeriod * 2)) + i*(1 / (samplingPeriod * transferFunctionLength));
		if (abs(F.at(i)) <= (cond1_if)) {
			transferFunction[i] = samplingPeriod;
		}
		else if ((abs(F.at(i))>cond1_if) && (abs(F.at(i)) <= cond2_if)){
			transferFunction[i] = (symbolPeriod / 2)*(1 + cos((PI*symbolPeriod / rollOffFactor)*(abs(F.at(i)) - ((1 - rollOffFactor) / (2 * symbolPeriod)))));
		}
		else {
			transferFunction[i] = 0;
		}
		transferFunction_normFactor +=  (transferFunction[i] * transferFunction[i]);
	};

	// Normalization to unit energy
	for (int i = 0; i < transferFunctionLength; i++) {
		transferFunction[i] = transferFunction[i] / sqrt(transferFunction_normFactor);
	}
};