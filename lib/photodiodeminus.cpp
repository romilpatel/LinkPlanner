#include <algorithm>
#include <complex>

#include "..\include\netxpto.h"
#include "..\include\photodiodeminus.h"


photodiodeminus::photodiodeminus(vector <Signal *> &InputSig, vector <Signal *> &OutputSig){

	numberOfInputSignals = InputSig.size();
	numberOfOutputSignals = OutputSig.size();

	inputSignals = InputSig;
	outputSignals = OutputSig;

	outputSignals[0]->symbolPeriod = inputSignals[0]->symbolPeriod;
	outputSignals[0]->samplingPeriod = inputSignals[0]->samplingPeriod;

	//setsign(sign);
}


bool photodiodeminus::runBlock(void){
	int ready0 = inputSignals[0]->ready();
	int ready = ready0;

	int space0 = outputSignals[0]->space();

	int process = min(ready, space0);

	if (process == 0) return false;
	
	for (int i = 0; i < process; i++) {

		t_complex x1;
		inputSignals[0]->bufferGet(&x1);
		t_real x1r = real(x1);
		t_real x1i = imag(x1);
		t_real radius = 0.0003;
		t_real E0 = 8.854187817e-12;

		t_real power = 2 * SPEED_OF_LIGHT * PI * radius*radius * E0 * (x1r*x1r + x1i*x1i) * 0.25;
		t_real current = 1 * power; // assuming power in wats, need to check if this is correct

		outputSignals[0]->bufferPut(-current);
	}
	return true;
}


/*
t_real photodiode::setsign( int sign ){
	if (sign=1)
	{
		SIGN = +1;
	}
	else if (sign=2)
	{
		SIGN = -1;
	}

	return SIGN;
}
*/