#include <algorithm>
#include <complex>

#include "netxpto.h"
#include "bit_decider.h"


void bit_decider::initialize(void){

	firstTime = false;

	outputSignals[0]->symbolPeriod=bitPeriod;
	outputSignals[0]->samplingPeriod = outputSignals[0]->symbolPeriod;
//	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());
}


bool bit_decider::runBlock(void){
	int ready = inputSignals[0]->ready();
	int space = outputSignals[0]->space();

	int process = min(ready, space);

	if (process == 0) return false;

	for (int i = 0; i < ready; i++) {

		t_real signalValue;
		inputSignals[0]->bufferGet(&signalValue);
		if (signalValue>0)
		{
			outputSignals[0]->bufferPut((t_binary) 0);
		}
		else if (signalValue<0)
		{
			outputSignals[0]->bufferPut((t_binary) 1);
		}
		else if (signalValue==0)
		{
			// do nothing
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