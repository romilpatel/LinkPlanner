#include <algorithm>
#include <complex>
#include <iostream>
#include <fstream>
#include <random>

#include "netxpto.h"
#include "testblock.h"


void testblock::initialize(void){

	firstTime = false;

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());

}


bool testblock::runBlock(void){
	ofstream myfile;
	myfile.open("translate.txt", fstream::app);

	int ready = inputSignals[0]->ready();
	int space = outputSignals[0]->space();

	int process = min(ready, space);

	if (process == 0) {
		myfile.close();
		return false;
	}
	
	t_real input;
	
	for (int i = 0; i < process; i++) {
		inputSignals[0]->bufferGet(&input);
		//translator[index] = input;
		//index++;
		myfile << input << "\n";
		outputSignals[0]->bufferPut(input);
	}
	return true;
	
}