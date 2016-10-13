#include <algorithm>
#include <complex>
#include <iostream>
#include <fstream>

#include "netxpto.h"
#include "BalancedBeamSplitter.h"


void BalancedBeamSplitter::initialize(void){

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
}


bool BalancedBeamSplitter::runBlock(void){
	int ready1 = inputSignals[0]->ready();
	int ready2 = inputSignals[1]->ready();
	int ready = min(ready1, ready2);

	int space1 = outputSignals[0]->space();
	int space2 = outputSignals[1]->space();
	int space = min(space1, space2);

	int process = min(ready, space);

	if (process == 0) return false;

	complex<t_real> imaginary(0, 1);
	
	for (int i = 0; i < process; i++) {

		t_complex ina;
		t_complex inb;
		inputSignals[0]->bufferGet(&ina);
		inputSignals[1]->bufferGet(&inb);
		


		t_complex outa = matrix[0]*ina + matrix[1]*inb;
		t_complex outb = matrix[2]*ina + matrix[3]*inb;

		outputSignals[0]->bufferPut(outa);
		outputSignals[1]->bufferPut(outb);

	}
	return true;
}
