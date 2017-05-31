# include "netxpto.h"
# include "ideal_amplifier.h"

# include <algorithm> // min

using namespace std;

void IdealAmplifier::initialize(void) {

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());
	
}

bool IdealAmplifier::runBlock(void) {

	int ready = inputSignals[0]->ready();
	int space = outputSignals[0]->space();

	int process = min(ready, space);

	if (process == 0) return false;

	signal_value_type sType = inputSignals[0]->getValueType();

	switch (sType) {
	case ComplexValue:
	{
						 t_complex in;
						 for (int k = 0; k < process; k++) {
							 inputSignals[0]->bufferGet(&in);
							 outputSignals[0]->bufferPut(gain*in);
						 }
						 break;
	}
	case ComplexValueXY:
	{
						   t_complex_xy inXY;
						   for (int k = 0; k < process; k++)
						   {
							   inputSignals[0]->bufferGet(&inXY);
							   t_complex_xy out = { inXY.x*gain, inXY.y*gain };
							   outputSignals[0]->bufferPut(out);
						   }
						   break;
	}
	}

	return true;
}