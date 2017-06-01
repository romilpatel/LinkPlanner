# include "netxpto.h"
# include "ideal_amplifier.h"

<<<<<<< HEAD
# include <algorithm.h> // min

using namespace std;

void IqModulator::initialize(void) {
=======
# include <algorithm> // min

using namespace std;

void IdealAmplifier::initialize(void){

>>>>>>> refs/remotes/origin/daniel

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());
<<<<<<< HEAD
	outputSignals[0]->centralWavelength(inputSignals[0]->centralWavelength);
	outputSignals[0]->centralFrequency(inputSignals[0]->centralFrequency);

}

bool IqModulator::runBlock(void) {
	
=======

}



bool IdealAmplifier::runBlock(void) {

>>>>>>> refs/remotes/origin/daniel
	int ready = inputSignals[0]->ready();
	int space = outputSignals[0]->space();

	int process = min(ready, space);

	if (process == 0) return false;
<<<<<<< HEAD

	switch (inputSignals[0]->type) {
		case t_complex:
			t_complex in;
			for (int k = 0; k < process; k++) {
				inputSignals[0]->bufferGet(&in);
				outputSignals[0]->bufferPut(gain*in);
			}
			break;
=======
	
	signal_value_type sTypeIn = inputSignals[0]->getValueType();
    signal_value_type sTypeOut= outputSignals[0]->getValueType();
    if (sTypeIn!=sTypeOut) {
        cout << "ERRO: ideal_amplifier.cpp (signal type mismatch!)" << "\n";
        return false;
    }

	switch (sTypeIn) {
	case RealValue:
	{
					  t_real inReal;
					  for (int k = 0; k < process; k++) {
						  inputSignals[0]->bufferGet(&inReal);
						  outputSignals[0]->bufferPut((t_real)gain*inReal);
					  }
					  break;
	}
	case ComplexValue:
	{
						 t_complex inComplexValue;
						 for (int k = 0; k < process; k++) {
							 inputSignals[0]->bufferGet(&inComplexValue);
							 outputSignals[0]->bufferPut((t_complex)gain*inComplexValue);
						 }
						 break;
	}
	case ComplexValueXY:
	{
						   t_complex_xy inComplexValueXY;
						   for (int k = 0; k < process; k++) {
							   inputSignals[0]->bufferGet(&inComplexValueXY);
							   t_complex_xy outComplexValueXY = { gain*inComplexValueXY.x, gain*inComplexValueXY.y };
							   outputSignals[0]->bufferPut(outComplexValueXY);
							   break;
						   }
						   break;
	}
>>>>>>> refs/remotes/origin/daniel
	}
	return true;
}
