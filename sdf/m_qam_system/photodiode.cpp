#include <algorithm>
#include <complex>

#include "netxpto.h"
#include "photodiode.h"


void Photodiode::initialize(void) {

	firstTime = false;

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

	outputSignals[0]->centralWavelength = outputOpticalWavelength;
	outputSignals[0]->centralFrequency = outputOpticalFrequency;

	outputSignals[1]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[1]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[1]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

	outputSignals[1]->centralWavelength = outputOpticalWavelength;
	outputSignals[1]->centralFrequency = outputOpticalFrequency;

	outputSignals[2]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[2]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[2]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

	outputSignals[2]->centralWavelength = outputOpticalWavelength;
	outputSignals[2]->centralFrequency = outputOpticalFrequency;

	outputSignals[3]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[3]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[3]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

	outputSignals[3]->centralWavelength = outputOpticalWavelength;
	outputSignals[3]->centralFrequency = outputOpticalFrequency;

}


bool Photodiode::runBlock(void) {
	int ready = inputSignals[0]->ready();

	int space1 = outputSignals[0]->space();
	int space2 = outputSignals[0]->space();
	int space = min(space1, space2);

	int process = min(ready, space);

	if (process == 0) return false;

	t_real radius = 0.0003; // radius of sensor
	t_real E0 = 8.854187817e-12;
	t_real n = 1.1;

	int nbOfInputSignals = 4;

	for (int i = 0; i < process; i++) {

		for (int j = 0; j <= nbOfInputSignals; j++) {

			t_complex input;
			inputSignals[j]->bufferGet(&input);

			t_real power = abs(input)*abs(input) * 2;
			t_real current = responsivity * power;

			outputSignals[j]->bufferPut(current);

		}
			//t_complex input1;
			//inputSignals[0]->bufferGet(&input1);
			//t_complex input2;
			//inputSignals[1]->bufferGet(&input2);
			//t_complex input3;
			//inputSignals[3]->bufferGet(&input3);
			//t_complex input4;
			//inputSignals[4]->bufferGet(&input4);

			//t_real power1 = abs(input1)*abs(input1) * 2;//sqrt(.5)/2*SPEED_OF_LIGHT*n*PI*radius*radius*E0*abs(input1)*abs(input1);
			//t_real current1 = responsivity * power1; // assuming power in wats, need to check if this is correct

			//t_real power2 = abs(input2)*abs(input2) * 2;// sqrt(.5)/2*SPEED_OF_LIGHT*n*PI*radius*radius*E0*abs(input2)*abs(input2);
			//t_real current2 = responsivity * power2; // assuming power in wats, need to check if this is correct

			//t_real power3 = abs(input3)*abs(input3) * 2;
			//t_real current3 = responsivity * power3;

			//t_real power4 = abs(input4)*abs(input4) * 2;
			//t_real current4 = responsivity * power4;


			//outputSignals[0]->bufferPut(current1);
			//outputSignals[1]->bufferPut(current2);

		
	}
	return true;
}