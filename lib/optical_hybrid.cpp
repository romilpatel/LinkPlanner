# include <algorithm>
# include <complex>
# include <iostream>
# include <fstream>
# include <random>

# include "netxpto.h"
# include "optical_hybrid.h"

using namespace std;


void OpticalHybrid::initialize(void) {

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

	/*outputSignals[0]->centralWavelength = outputOpticalWavelength;
	outputSignals[0]->centralFrequency = outputOpticalFrequency;*/

	outputSignals[1]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[1]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[1]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

	/*outputSignals[1]->centralWavelength = outputOpticalWavelength;
	outputSignals[1]->centralFrequency = outputOpticalFrequency;*/

	outputSignals[2]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[2]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[2]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

	/*outputSignals[2]->centralWavelength = outputOpticalWavelength;
	outputSignals[2]->centralFrequency = outputOpticalFrequency;*/

	outputSignals[3]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[3]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[3]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

	/*outputSignals[3]->centralWavelength = outputOpticalWavelength;
	outputSignals[3]->centralFrequency = outputOpticalFrequency;*/

	/*outputSignals[0]->setSamplingPeriod(samplingPeriod);
	outputSignals[0]->setCentralWavelength(outputOpticalWavelength);
	outputSignals[0]->setCentralFrequency(outputOpticalFrequency);

	outputSignals[1]->setSamplingPeriod(samplingPeriod);
	outputSignals[1]->setCentralWavelength(outputOpticalWavelength);
	outputSignals[1]->setCentralFrequency(outputOpticalFrequency);

	outputSignals[2]->setSamplingPeriod(samplingPeriod);
	outputSignals[2]->setCentralWavelength(outputOpticalWavelength);
	outputSignals[2]->setCentralFrequency(outputOpticalFrequency);

	outputSignals[3]->setSamplingPeriod(samplingPeriod);
	outputSignals[3]->setCentralWavelength(outputOpticalWavelength);
	outputSignals[3]->setCentralFrequency(outputOpticalFrequency);*/
}

bool OpticalHybrid::runBlock(void) {

	int ready0 = inputSignals[0]->ready();
	int ready1 = inputSignals[1]->ready();
	int ready = min(ready0, ready1);

	int space = outputSignals[0]->space();

	int process = min(ready, space);

	if (process == 0) return false;

	t_complex Signal, LO;

	complex<double> imaginary(0, 1);

	t_complex OutputSignal1; //=Signal+LO
	t_complex OutputSignal2; //=Signal-LO
	t_complex OutputSignal3; //=Signal+i*LO
	t_complex OutputSignal4; //=Signal-i*LO


	for (int k = 0; k < process; k++) {

		inputSignals[0]->bufferGet(&Signal);
		inputSignals[1]->bufferGet(&LO);

		OutputSignal1 = Signal + LO;
		OutputSignal2 = Signal - LO;
		OutputSignal3 = Signal + imaginary*LO;
		OutputSignal4 = Signal - imaginary*LO;

		outputSignals[0]->bufferPut(OutputSignal1);
		outputSignals[1]->bufferPut(OutputSignal2);
		outputSignals[2]->bufferPut(OutputSignal3);
		outputSignals[3]->bufferPut(OutputSignal4);

	}

	return true;
}