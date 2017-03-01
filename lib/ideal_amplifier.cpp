<<<<<<< HEAD
#include <algorithm>  // min()
#include <complex>
=======
# include "netxpto.h"
# include "ideal_amplifier.h"
>>>>>>> 14adca355faa92683b01e2a95152ddb168447487

# include <algorithm> // min

using namespace std;

<<<<<<< HEAD
void IdealAmplifier::initialize(void){
=======
void IdealAmplifier::initialize(void) {
>>>>>>> 14adca355faa92683b01e2a95152ddb168447487

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());
<<<<<<< HEAD

}


bool IdealAmplifier::runBlock(void){
=======
	
}

bool IdealAmplifier::runBlock(void) {
>>>>>>> 14adca355faa92683b01e2a95152ddb168447487

	int ready = inputSignals[0]->ready();
	int space = outputSignals[0]->space();

	int process = min(ready, space);

	if (process == 0) return false;
<<<<<<< HEAD
	
	signal_value_type sType = inputSignals[0]->getValueType();

	switch (sType) {
		case RealValue:
			t_real inReal;
			for (int k = 0; k < process; k++) {
				inputSignals[0]->bufferGet(&inReal);
				outputSignals[0]->bufferPut((t_real)gain*inReal);
			}
			break;
		case ComplexValue:
			t_complex inComplexValue;
			for (int k = 0; k < process; k++) {
				inputSignals[0]->bufferGet(&inComplexValue);
				outputSignals[0]->bufferPut((t_complex)gain*inComplexValue);
			}
			break;
		case ComplexValueXY:
			t_complex_xy inComplexValueXY;
			for (int k = 0; k < process; k++) {
				inputSignals[0]->bufferGet(&inComplexValueXY);
				outputSignals[0]->bufferPut((t_complex_xy) { gain*inComplexValueXY.x, gain*inComplexValueXY.y });
				break;
			}
			break;
=======

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
>>>>>>> 14adca355faa92683b01e2a95152ddb168447487
	}
	}

	return true;
}