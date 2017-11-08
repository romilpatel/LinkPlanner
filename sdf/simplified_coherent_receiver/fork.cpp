#include "netxpto.h"

#include "fork.h"

using namespace std;

void fork::initialize(void)
{
	double samplingPeriod1 = inputSignals[0]->samplingPeriod;			// Signal arrives from pulse_shapper output 
	double symbolPeriod1 = inputSignals[0]->symbolPeriod;
}



bool fork::runBlock(void)
{

	int ready = inputSignals[0]->ready();
	int space1 = outputSignals[0]->space();
	int space2 = outputSignals[1]->space();

	int space = (space1 <= space2) ? space1 : space2;
	int length = (ready <= (2 * space)) ? ready : space; // equivalent to min(ready, 2 * space);

	if (length <= 0) return false;


	for (int i = 0; i < length; i++) {
		t_real s6;
		inputSignals[0]->bufferGet(&s6);
		
		outputSignals[0]->bufferPut((t_real)(s6));
		outputSignals[1]->bufferPut((t_real)(s6));
	}

	return true;

}

