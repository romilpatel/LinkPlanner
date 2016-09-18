#include <algorithm>
#include <complex>

#include "netxpto.h"
#include "bit_error_rate.h"


bit_error_rate::bit_error_rate(vector <Signal *> &InputSig, vector <Signal *> &OutputSig){

	numberOfInputSignals = InputSig.size();
	numberOfOutputSignals = OutputSig.size();

	inputSignals = InputSig;
	outputSignals = OutputSig;

	outputSignals[0]->symbolPeriod = inputSignals[0]->symbolPeriod;
	outputSignals[0]->samplingPeriod = inputSignals[0]->samplingPeriod;

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
		myfile << "BER=" << BER << "\%";
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
		}



		outputSignals[0]->bufferPut(&signalValue);

	}
	return true;

}