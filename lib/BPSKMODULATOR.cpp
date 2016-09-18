# include <algorithm>	// std::min

# include "..\include\netxpto.h"
# include "..\include\BPSKMODULATOR.h"


using namespace std;


BPSKMODULATOR::BPSKMODULATOR(vector <Signal *> &InputSig, vector <Signal *> &OutputSig){

	numberOfInputSignals = InputSig.size();
	numberOfOutputSignals = OutputSig.size();

	inputSignals = InputSig;
	outputSignals = OutputSig;

	outputSignals[0]->symbolPeriod = inputSignals[0]->symbolPeriod;
	outputSignals[0]->samplingPeriod = inputSignals[0]->samplingPeriod;
}


bool BPSKMODULATOR::runBlock(void){

	if (firstTime) {

		firstTime = false;

		outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
		outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
		int aux = inputSignals[0]->getFirstValueToBeSaved();
		outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

		outputSignals[0]->centralWavelength = outputOpticalWavelength;
		outputSignals[0]->centralFrequency = outputOpticalFrequency;

	}

	int ready0 = inputSignals[0]->ready();
	int ready = ready0;

	int space = outputSignals[0]->space();

	int process = min(ready, space);

	if (process == 0) return false;
	int auxint=0;
	t_binary signalValue;
	t_real re = sqrt(2) / 2;
	t_real im = sqrt(2) / 2;
	for (int i = 0; i < process; i++) {

		auxint++;

		inputSignals[0]->bufferGet(&signalValue);
		if (auxint==1)
		{
			if (signalValue==0)
			{
				im = sqrt(2) / 2;
			}
			if (signalValue==1)
			{
				im = -sqrt(2) / 2;
			}
		}

		if (auxint==2)
		{
			auxint = 0;
			complex<t_real> myComplex(re, im);
			myComplex = .5*sqrt(outputOpticalPower)*myComplex;
			outputSignals[0]->bufferPut(myComplex);
		}

		
		
		
	}

	return true;
}
