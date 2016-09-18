# include <complex>
# include <fstream>
# include <iostream>
# include <math.h>
# include <stdio.h>
# include <string>
# include <strstream>
# include <vector>
# include <algorithm>

# include "..\include\netxpto.h"
# include "..\include\bpsk_mapper.h"


using namespace std;

bpsk_mapper::bpsk_mapper(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) {
     
  numberOfInputSignals = InputSig.size();
  numberOfOutputSignals = OutputSig.size();

  inputSignals = InputSig;
  outputSignals = OutputSig;
 
  outputSignals[0]->symbolPeriod = 2 * (inputSignals[0]->symbolPeriod);
  outputSignals[0]->samplingPeriod = 1 * inputSignals[0]->samplingPeriod;

  //outputSignals[1]->symbolPeriod = 2 * (inputSignals[0]->symbolPeriod);
  //outputSignals[1]->samplingPeriod = 2 * inputSignals[0]->samplingPeriod;

}

bool bpsk_mapper::runBlock(void) {


	int ready = inputSignals[0]->ready();
	int space1 = outputSignals[0]->space();
	//int space2 = outputSignals[1]->space();

	int space = space1; //(space1 <= space2) ? space1 : space2;
	int length = (ready <= (2 * space)) ? ready : space; // equivalent to min(ready, 2 * space);
	int binaryValue;
	if (length <= 0) return false;

	for (int i = 0; i < length; i++) {
		//bool binaryValue;
		inputSignals[0]->bufferGet(&binaryValue);
		outputSignals[0]->bufferPut(1);
	}

	return true;
}

