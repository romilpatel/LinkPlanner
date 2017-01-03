#include <algorithm>
#include <complex>

#include "netxpto.h"
#include "photodiode.h"
<<<<<<< HEAD


void Photodiode::initialize(void) {
=======
#include <random>


void Photodiode::initialize(void){
>>>>>>> dc00d875a4698894f7854fe56be177086bf2b48b

	firstTime = false;

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

	outputSignals[0]->centralWavelength = outputOpticalWavelength;
	outputSignals[0]->centralFrequency = outputOpticalFrequency;

}


<<<<<<< HEAD
bool Photodiode::runBlock(void) {

	int ready0 = inputSignals[0]->ready();
	int ready1 = inputSignals[1]->ready();
	int ready = min(ready0, ready1);

	int space = outputSignals[0]->space();
=======
bool Photodiode::runBlock(void){
	int ready = inputSignals[0]->ready();

/*	normal_distribution<double> distribution(0, 1);
	t_real dt = inputSignals[0]->getSamplingPeriod();
	t_real noise1;
	t_real noise2;
*/
	int space1 = outputSignals[0]->space();
	int space2 = outputSignals[0]->space();
	int space = min(space1, space2);
>>>>>>> dc00d875a4698894f7854fe56be177086bf2b48b

	int process = min(ready, space);

	if (process == 0) return false;

	t_real radius = 0.0003; // radius of sensor
	t_real E0 = 8.854187817e-12;
	t_real n = 1.1;
<<<<<<< HEAD

	for (int i = 0; i < process; i++) {

			t_complex inputSignal1;
			t_complex inputSignal2;

			inputSignals[0]->bufferGet(&inputSignal1);
			inputSignals[1]->bufferGet(&inputSignal2);

			t_real power1 = abs(inputSignal1)*abs(inputSignal1) * 2;
			t_real current1 = responsivity * power1;

			t_real power2 = abs(inputSignal2)*abs(inputSignal2) * 2;
			t_real current2 = responsivity * power2;

			t_real outputSignal = current1 - current2;

			outputSignals[0]->bufferPut(outputSignal);

		
	}
	return true;
}
=======
	
	for (int i = 0; i < process; i++) {

	/*	noise1 = distribution(generator1);
		noise2 = distribution(generator2);*/

		t_complex input1;
		inputSignals[0]->bufferGet(&input1);
		t_complex input2;
		inputSignals[1]->bufferGet(&input2);



		t_real power1 = abs(input1)*abs(input1) * 4;//sqrt(.5)/2*SPEED_OF_LIGHT*n*PI*radius*radius*E0*abs(input1)*abs(input1);
		t_real current1 = responsivity * power1; // +sqrt(h*SPEED_OF_LIGHT / dt)*noise1*(sqrt(power1) + 1 / 2)); // assuming power in wats, need to check if this is correct

		t_real power2 = abs(input2)*abs(input2) * 4;// sqrt(.5)/2*SPEED_OF_LIGHT*n*PI*radius*radius*E0*abs(input2)*abs(input2);
		t_real current2 = responsivity * power2; // +sqrt(h*SPEED_OF_LIGHT / dt)*noise2*(sqrt(power2) + 1 / 2)); // assuming power in wats, need to check if this is correct

		t_real out = current1 - current2;

		outputSignals[0]->bufferPut(out);
	}
	return true;
}
>>>>>>> dc00d875a4698894f7854fe56be177086bf2b48b
