#include "homodyne_receiver.h"


HomodyneReceiver::HomodyneReceiver(vector<Signal *> &inputSignal, vector<Signal *> &outputSignal) :SuperBlock(inputSignal, outputSignal) {

	setLocalOscillatorSamplingPeriod(inputSignal[0]->getSamplingPeriod());

	B1.initializeBlock(vector<Signal*> { }, vector<Signal*> { &HMD01 });
	B2.initializeBlock(vector<Signal*> { &HMD00, &HMD01 }, vector<Signal*> { &HMD02, &HMD03, &HMD04, &HMD05 });
	B3.initializeBlock(vector<Signal*> { &HMD02, &HMD03 }, vector<Signal*> { &HMD06 });
	B4.initializeBlock(vector<Signal*> { &HMD04, &HMD05 }, vector<Signal*> { &HMD07 });
	B5.initializeBlock(vector<Signal*> { &HMD06 }, vector<Signal*> { &HMD08 });
	B6.initializeBlock(vector<Signal*> { &HMD07 }, vector<Signal*> { &HMD09 });
	B7.initializeBlock(vector<Signal*> { &HMD08 }, vector<Signal*> { &HMD10 });
	B8.initializeBlock(vector<Signal*> { &HMD09 }, vector<Signal*> { &HMD11 });
	B9.initializeBlock(vector<Signal*> { &HMD10, &HMD11 }, vector<Signal*> { &HMD12 });

	setModuleBlocks({ &B1, &B2, &B3, &B4, &B5, &B6, &B7, &B8, &B9 });
	
};
