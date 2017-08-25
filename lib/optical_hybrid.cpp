<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil
#include <algorithm>
#include <complex>
#include <iostream>
#include <fstream>

#include "netxpto.h"
#include "optical_hybrid.h"


void OpticalHybrid::initialize(void){

	firstTime = false;
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
# include <algorithm>
# include <complex>
# include <iostream>
# include <fstream>
# include <random>

# include "netxpto.h"
# include "optical_hybrid.h"

using namespace std;


void OpticalHybrid::initialize(void) {
>>>>>>> AnaLuisa
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());
<<<<<<< HEAD
<<<<<<< HEAD
	 
	outputSignals[0]->setCentralWavelength(inputSignals[0]->getCentralWavelength());
	outputSignals[0]->setCentralFrequency(inputSignals[0]->getCentralFrequency());
=======
<<<<<<< HEAD
	 
	outputSignals[0]->setCentralWavelength(inputSignals[0]->getCentralWavelength());
	outputSignals[0]->setCentralFrequency(inputSignals[0]->getCentralFrequency());
=======

	/*outputSignals[0]->centralWavelength = outputOpticalWavelength;
	outputSignals[0]->centralFrequency = outputOpticalFrequency;*/
>>>>>>> AnaLuisa
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
	 
	outputSignals[0]->setCentralWavelength(inputSignals[0]->getCentralWavelength());
	outputSignals[0]->setCentralFrequency(inputSignals[0]->getCentralFrequency());
>>>>>>> Romil

	outputSignals[1]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[1]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[1]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

<<<<<<< HEAD
<<<<<<< HEAD
	outputSignals[1]->setCentralWavelength(inputSignals[1]->getCentralWavelength());
	outputSignals[1]->setCentralFrequency(inputSignals[1]->getCentralFrequency());
=======
<<<<<<< HEAD
	outputSignals[1]->setCentralWavelength(inputSignals[1]->getCentralWavelength());
	outputSignals[1]->setCentralFrequency(inputSignals[1]->getCentralFrequency());
=======
	/*outputSignals[1]->centralWavelength = outputOpticalWavelength;
	outputSignals[1]->centralFrequency = outputOpticalFrequency;*/
>>>>>>> AnaLuisa
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
	outputSignals[1]->setCentralWavelength(inputSignals[1]->getCentralWavelength());
	outputSignals[1]->setCentralFrequency(inputSignals[1]->getCentralFrequency());
>>>>>>> Romil

	outputSignals[2]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[2]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[2]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

<<<<<<< HEAD
<<<<<<< HEAD
	outputSignals[2]->setCentralWavelength(inputSignals[0]->getCentralWavelength());
	outputSignals[2]->setCentralFrequency(inputSignals[0]->getCentralFrequency());
=======
<<<<<<< HEAD
	outputSignals[2]->setCentralWavelength(inputSignals[0]->getCentralWavelength());
	outputSignals[2]->setCentralFrequency(inputSignals[0]->getCentralFrequency());
=======
	/*outputSignals[2]->centralWavelength = outputOpticalWavelength;
	outputSignals[2]->centralFrequency = outputOpticalFrequency;*/
>>>>>>> AnaLuisa
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
	outputSignals[2]->setCentralWavelength(inputSignals[0]->getCentralWavelength());
	outputSignals[2]->setCentralFrequency(inputSignals[0]->getCentralFrequency());
>>>>>>> Romil

	outputSignals[3]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[3]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[3]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil
	outputSignals[3]->setCentralWavelength(inputSignals[1]->getCentralWavelength());
	outputSignals[3]->setCentralFrequency(inputSignals[1]->getCentralFrequency());
}


bool OpticalHybrid::runBlock(void){
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
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
>>>>>>> AnaLuisa
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil

	int ready0 = inputSignals[0]->ready();
	int ready1 = inputSignals[1]->ready();
	int ready = min(ready0, ready1);

<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil
	int space0 = outputSignals[0]->space();
	int space1 = outputSignals[1]->space();
	int space2 = outputSignals[2]->space();
	int space3 = outputSignals[3]->space();
	int spacea = min(space0, space1);
	int spaceb = min(space2, space3);
	int space = min(spacea, spaceb);
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
	int space = outputSignals[0]->space();
>>>>>>> AnaLuisa
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil

	int process = min(ready, space);

	if (process == 0) return false;

<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil
	complex<double> imaginary(0, 1);
	
	complex<double> div(0.5, 0);

	for (int i = 0; i < process; i++) {

		t_complex ina;
		t_complex inb;
		inputSignals[0]->bufferGet(&ina);
		inputSignals[1]->bufferGet(&inb);

		t_complex outa = div * ina + div * inb;
		t_complex outb = div * ina - div * inb;
		t_complex outc = div * ina + imaginary*div * inb;
		t_complex outd = div * ina - imaginary*div * inb;
		outputSignals[0]->bufferPut((t_complex) outa);
		outputSignals[1]->bufferPut((t_complex) outb);
		outputSignals[2]->bufferPut((t_complex) outc);
		outputSignals[3]->bufferPut((t_complex) outd);

	}
	return true;
}
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
	t_complex Signal, LO;

	complex<double> imaginary(0, 1);

	t_complex OutputSignal1; //=Signal+LO
	t_complex OutputSignal2; //=Signal-LO
	t_complex OutputSignal3; //=Signal+i*LO
	t_complex OutputSignal4; //=Signal-i*LO


	for (int k = 0; k < process; k++) {

		inputSignals[0]->bufferGet(&Signal);
		inputSignals[1]->bufferGet(&LO);

		OutputSignal1 = powerFactor*(Signal + LO);
		OutputSignal2 = powerFactor*(Signal - LO);
		OutputSignal3 = powerFactor*(Signal + imaginary*LO);
		OutputSignal4 = powerFactor*(Signal - imaginary*LO);

		outputSignals[0]->bufferPut(OutputSignal1);
		outputSignals[1]->bufferPut(OutputSignal2);
		outputSignals[2]->bufferPut(OutputSignal3);
		outputSignals[3]->bufferPut(OutputSignal4);

	}

	return true;
}
>>>>>>> AnaLuisa
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil
