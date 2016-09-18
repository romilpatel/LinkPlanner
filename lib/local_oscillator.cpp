# include "local_oscillator.h"

local_oscillator::local_oscillator(vector<Signal *> &InputSig, vector<Signal *> &OutputSig){

	inputSignals = InputSig;
	outputSignals = OutputSig;

	outputSignals[0]->symbolPeriod = B5.outputSignals[0]->symbolPeriod;
	outputSignals[0]->samplingPeriod = B5.outputSignals[0]->samplingPeriod;

	ModuleBlocks = { &B1, &B2, &B3, &B4, &B5 };

}

local_oscillator::~local_oscillator(void) {

	for (int unsigned i = 0; i < ModuleBlocks.size(); i++) {
		ModuleBlocks[i]->terminateBlock();
	}

	for (int unsigned j = 0; j<(ModuleBlocks[ModuleBlocks.size() - 1]->outputSignals).size(); j++)
		ModuleBlocks[ModuleBlocks.size()-1]->outputSignals[0]->close();
}

bool local_oscillator::runBlock() {

	if (firstTime) {

		for (int unsigned i = 0; i < ModuleBlocks.size(); i++) {
			for (int unsigned j = 0; j<(ModuleBlocks[i]->inputSignals).size(); j++) {
				(ModuleBlocks[i]->inputSignals[j])->writeHeader();
			}
		}

		for (int unsigned j = 0; j<(ModuleBlocks[ModuleBlocks.size() - 1]->outputSignals).size(); j++)
			ModuleBlocks[ModuleBlocks.size() - 1]->outputSignals[j]->writeHeader();
	}

	bool Alive{ false };

	bool Continue{ true };
	do {

		Continue = false;

		for (unsigned int i = 0; i < ModuleBlocks.size(); i++) {
			bool aux = ModuleBlocks[i]->runBlock();
			Continue = (Continue || aux);
			Alive = (Alive || Continue);
		}

		if (firstTime) {

			firstTime = false;

			outputSignals[0]->setSymbolPeriod(ModuleBlocks[ModuleBlocks.size() - 1]->outputSignals[0]->getSymbolPeriod());
			outputSignals[0]->setSamplingPeriod(ModuleBlocks[ModuleBlocks.size() - 1]->outputSignals[0]->getSamplingPeriod());
			outputSignals[0]->setFirstValueToBeSaved(ModuleBlocks[ModuleBlocks.size() - 1]->outputSignals[0]->getFirstValueToBeSaved());

		}

		int ready = ModuleBlocks[ModuleBlocks.size() - 1]->outputSignals[0]->ready();
		int space = outputSignals[0]->space();
		int length = (ready <= space) ? ready : space;

		t_complex signalValue;
		for (int i = 0; i < length; i++) {
				ModuleBlocks[ModuleBlocks.size() - 1]->outputSignals[0]->bufferGet(&signalValue);
				outputSignals[0]->bufferPut(signalValue);
		}
		

	} while (Continue);

	return Alive;
}


void local_oscillator::setBitPeriod(double bPeriod) {

	B1.setBitPeriod(bPeriod);

	S1.setSymbolPeriod(bPeriod); 
	S1.setSamplingPeriod(bPeriod);

	S2.setSymbolPeriod(2*bPeriod);
	S2.setSamplingPeriod(bPeriod);



	S4.setSymbolPeriod(S3.getSymbolPeriod());
	S4.setSamplingPeriod(S3.getSamplingPeriod());
	
	S5.setSymbolPeriod(S4.getSymbolPeriod());
	S5.setSamplingPeriod(S4.getSamplingPeriod());

	outputSignals[0]->setSymbolPeriod(S5.getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(S5.getSamplingPeriod());

};

void local_oscillator::setNumberOfSamplesPerSymbol(int n) {

//	B3.numberOfSamplesPerSymbol = n;  

//	S3.setSymbolPeriod(S2.getSymbolPeriod());
//	S3.setSamplingPeriod(S2.getSamplingPeriod() / B3.numberOfSamplesPerSymbol);

	outputSignals[0]->setSymbolPeriod(S5.getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(S5.getSamplingPeriod());

};

void local_oscillator::setBuffersLength(int bLength) {
	S1.bufferLength = bLength;
	S2.bufferLength = bLength;
	S3.bufferLength = bLength;
	S4.bufferLength = bLength;
	S5.bufferLength = bLength;
};

void local_oscillator::setSaveInternalSignals(bool sSignals) {
	
	if (sSignals) {
		
		saveInternalSignals = true;

		S1.setFileName("MQAM1.sgn");
		S2.setFileName("MQAM2.sgn");
		S3.setFileName("MQAM3.sgn");
		S4.setFileName("MQAM4.sgn");
		S5.setFileName("MQAM5.sgn");
	}

	return;
}

