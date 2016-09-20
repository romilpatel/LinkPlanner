#include <algorithm>
#include <complex>

#include "netxpto.h"
#include "bit_error_rate.h"

void bit_error_rate::initialize(void){
	firstTime = false;

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());
}


bool bit_error_rate::runBlock(void){
	int ready = inputSignals[0]->ready();
	int space = outputSignals[0]->space();

	int process = min(ready, space);

	float NumberOfBits = recievedbits;
	float Coincidences = coincidences;

	float BER;
	BER = (NumberOfBits - Coincidences) / NumberOfBits * 100;

	if (process == 0)
	{
		ofstream myfile;
		myfile.open("BER.txt");
		myfile << "BER=" << BER << "\% \n";
		myfile << "Number of recieved bits =" << NumberOfBits << "\n";
		myfile.close();
		return false;
	}



	for (int i = 0; i < process; i++) {

		t_binary signalValue;
		inputSignals[0]->bufferGet(&signalValue);
		t_binary SignalValue;
		inputSignals[1]->bufferGet(&SignalValue);

		recievedbits++;

		if (signalValue == SignalValue)
		{
			coincidences++;
			outputSignals[0]->bufferPut(1);
		}
		else
		{
			outputSignals[0]->bufferPut(0);
		}




	}
	return true;

}