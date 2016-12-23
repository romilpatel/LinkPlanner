#include "i_homodyne_receiver.h"


I_HomodyneReceiver::I_HomodyneReceiver(vector<Signal *> &inputSignal, vector<Signal *> &outputSignal) :SuperBlock(inputSignal, outputSignal) {

	inputSignals = inputSignal;
	outputSignals = outputSignal;
};

void I_HomodyneReceiver::initialize(void) {
	
	setLocalOscillatorSamplingPeriod(inputSignals[0]->getSamplingPeriod());

	B1.initializeBlock(vector<Signal*> { }, vector<Signal*> { &I_HMD01 });
	B2.initializeBlock(vector<Signal*> { inputSignals[0], &I_HMD01 }, vector<Signal*> { &I_HMD02, &I_HMD03 });
	B3.initializeBlock(vector<Signal*> { &I_HMD02, &I_HMD03 }, vector<Signal*> { &I_HMD04 });
	B4.initializeBlock(vector<Signal*> { &I_HMD04 }, vector<Signal*> { &I_HMD05 });
	B5.initializeBlock(vector<Signal*> { &I_HMD05 }, vector<Signal*> { &I_HMD06 });
	B6.initializeBlock(vector<Signal*> { &I_HMD06 }, vector<Signal*> { outputSignals[0] });

	setModuleBlocks({ &B1, &B2, &B3, &B4, &B5, &B6 });

}