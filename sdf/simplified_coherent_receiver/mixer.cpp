#include "netxpto.h"

#include "mixer.h"

using namespace std;

void mixer::initialize(void)
{
	double samplingPeriod1 = inputSignals[0]->samplingPeriod;			// Signal arrives from pulse_shapper output 
	double symbolPeriod1  = inputSignals[0]->symbolPeriod;

	double samplingPeriod2 = inputSignals[1]->samplingPeriod;			// Signal arrives from RF_Osclillator output
	double symbolPeriod2  = inputSignals[1]->symbolPeriod;

	if (samplingPeriod1 != samplingPeriod2) { cout << "ERROR: Mixer.cpp - samplingPeriod\n"; };
	
	outputSignals[0]->setSamplingPeriod(samplingPeriod1);

	if (symbolPeriod1 == 1 && symbolPeriod2 == 1) { cout << "ERROR: Mixer.cpp - symbolPeriod\n"; };

	if (symbolPeriod1 == 1) {
		outputSignals[0]->setSymbolPeriod(symbolPeriod2);
	} 
	else {
		outputSignals[0]->setSymbolPeriod(symbolPeriod1);
	};
}


bool mixer::runBlock(void)
{

	int ready1 = inputSignals[0]->ready();
	int ready2 = inputSignals[1]->ready();
	int space = outputSignals[0]->space();

	int process = min(space, min(ready1, ready2));
	if (process == 0) return false;

	for (int i = 0; i < process; i++) {
		t_real s1, s2;
		inputSignals[0]->bufferGet(&s1);
		inputSignals[1]->bufferGet(&s2);
		outputSignals[0]->bufferPut((t_real)(s1*s2));
	}

	return true;

}

