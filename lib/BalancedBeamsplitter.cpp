#include <algorithm>
#include <complex>
#include <iostream>
#include <fstream>

#include "netxpto.h"
#include "BalancedBeamsplitter.h"


void BalancedBeamsplitter::initialize(void){

	firstTime = false;

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());
	 
	outputSignals[0]->centralWavelength = outputOpticalWavelength;
	outputSignals[0]->centralFrequency = outputOpticalFrequency;
}


bool BalancedBeamsplitter::runBlock(void){
	int ready = inputSignals[0]->ready();
	int space = outputSignals[0]->space();

	int process = min(ready, space);

	if (process == 0) return false;

	complex<t_real> imaginary(0, 1);
	
	for (int i = 0; i < process; i++) {

		t_complex_xy input;
		inputSignals[0]->bufferGet(&input);

		t_complex x = input.x;
		t_complex y = input.y;
		

		t_complex outa = div*(x + y);
		t_complex outb = div*(x - y);

		t_complex_xy output = { outa, outb };
		outputSignals[0]->bufferPut(output);

	}
	return true;
}
