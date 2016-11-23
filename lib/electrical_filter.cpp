#include <algorithm>
#include <complex>
#include <iostream>

#include "netxpto.h"
#include "electrical_filter.h"


void ElectricalFilter::initialize(void){

	firstTime = false;

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
}


bool ElectricalFilter::runBlock(void){
	int ready = inputSignals[0]->ready();
	

	int space = outputSignals[0]->space();
	int process = min(ready, space);
	int auxint = sampling-1;

	t_real in;
	t_real out;

	ofstream translate;
	translate.open("translate.txt", fstream::app);

	if (process == 0)
	{
		translate.close();
		return false;
	}

	for (int i = 0; i < ready; i++) {

		
		inputSignals[0]->bufferGet(&in);
		auxint = auxint + 1;

		

		if (auxint == sampling)
		{
			auxint = 0;
			AuxInt++;
			if (AuxInt>=delay)
			{
				out = in;
				outputSignals[0]->bufferPut(out);
				translate << out << "\n";

			}
		}

	}

	return true;
}