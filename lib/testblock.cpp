#include "testblock.h"


testblock::testblock(vector<Signal *> &inputSignal, vector<Signal *> &outputSignal) :SuperBlock(inputSignal, outputSignal) {

	numberOfInputSignals = inputSignal.size();
	numberOfOutputSignals = outputSignal.size();

	B1.initializeBlock(vector<Signal*> { inputSignal }, vector<Signal*> { &HMD00, &HMD01 });
	B2.initializeBlock(vector<Signal*> { &HMD00, &HMD01 }, vector<Signal*> { &HMD02, &HMD03 });
	B3.initializeBlock(vector<Signal*> { &HMD02, &HMD03 }, vector<Signal*> { &HMD04, &HMD05 });
	B4.initializeBlock(vector<Signal*> { &HMD04, &HMD05 }, vector<Signal*> { &HMD06});
	B5.initializeBlock(vector<Signal*> { &HMD06 }, vector<Signal*> { &HMD07 });
	B6.initializeBlock(vector<Signal*> { &HMD07 }, vector<Signal*> { &HMD08 });
	B7.initializeBlock(vector<Signal*> { &HMD08 }, vector<Signal*> { &HMD09 });
	B8.initializeBlock(vector<Signal*> { &HMD09 }, vector<Signal*> { outputSignal });

	setModuleBlocks({ &B1, &B2, &B3, &B4, &B5, &B6, &B7, &B8 });
	
};
/*
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
	
}*/

/* translate block */

//////////////////////////////////////////////////////
//ofstream translate;
//translate.open("translate.txt", fstream::app);

//	int process = min(ready, space);

//////////////////////////////////////////////////////

//translate.close();

//////////////////////////////////////////////////////
//translate << 0 << "\n";
//////////////////////////////////////////////////////
