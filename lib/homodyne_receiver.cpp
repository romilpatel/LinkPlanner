#include "homodyne_receiver.h"


HomodyneReceiver::HomodyneReceiver(vector<Signal *> &inputSignal, vector<Signal *> &outputSignal) :SuperBlock(inputSignal, outputSignal) {

	setLocalOscillatorSamplingPeriod(inputSignal[0]->getSamplingPeriod());

	B1.initializeBlock(vector<Signal*> { inputSignal }, vector<Signal*> { &HMD01 });
	B2.initializeBlock(vector<Signal*> { &HMD00, &HMD01 }, vector<Signal*> { &HMD02, &HMD03 });
	B3.initializeBlock(vector<Signal*> { &HMD02, &HMD03 }, vector<Signal*> { &HMD04 });
	B4.initializeBlock(vector<Signal*> { &HMD04 }, vector<Signal*> { &HMD05 });
	B5.initializeBlock(vector<Signal*> { &HMD05 }, vector<Signal*> { &HMD06 });
	B6.initializeBlock(vector<Signal*> { &HMD06 }, vector<Signal*> { outputSignal });

	setModuleBlocks({ &B1, &B2, &B3, &B4, &B5, &B6 });
	
};
