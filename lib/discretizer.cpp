#include <algorithm>
#include <complex>

#include "netxpto.h"
#include "discretizer.h"


discretizer::discretizer(vector <Signal *> &InputSig, vector <Signal *> &OutputSig){

	numberOfInputSignals = InputSig.size();
	numberOfOutputSignals = OutputSig.size();

	inputSignals = InputSig;
	outputSignals = OutputSig;

	outputSignals[0]->symbolPeriod = inputSignals[0]->symbolPeriod;;
	outputSignals[0]->samplingPeriod = 16*inputSignals[0]->samplingPeriod;
}


bool discretizer::runBlock(void){
	int ready = inputSignals[0]->ready();
	int delay = 100;
	int period = 16;

	int space0 = outputSignals[0]->space();


	int process = min(ready, space0);

	t_real out;

	if (process == 0) return false;

	int auxint = 15;

	for (int i = 0; i < ready; i++) {

		t_real signalValue;
		inputSignals[0]->bufferGet(&signalValue);
		auxint = auxint + 1;

		if (auxint == period)
		{
			auxint = 0;
			out = signalValue;
			outputSignals[0]->bufferPut(out);
		}

	}

	return true;
}

/*
void bit_decider::setBitPeriod(double bPeriod){
bitPeriod = bPeriod;
outputSignals[0]->symbolPeriod = bitPeriod;
outputSignals[0]->samplingPeriod = outputSignals[0]->symbolPeriod;
};


class ContinuousToDiscreteTime : public Block {
public:
ContinuousToDiscreteTime(vector<Signal *> &InputSig, vector<Signal *> &OutputSig);
bool runBlock(void);

int numberOfSamplesPerSymbol{ 8 };
int index{ 0 };

void setNumberOfSamplesPerSymbol(int nSamplesPerSymbol){ numberOfSamplesPerSymbol = nSamplesPerSymbol; outputSignals[0]->samplingPeriod = (inputSignals[0]->samplingPeriod) / numberOfSamplesPerSymbol; };
};
*/