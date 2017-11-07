
# include "netxpto.h";
#include "mixer.h";

using namespace std;

void mixer::initialize(void)
{
	double sampingPeriod = inputSignals[0]->samplingPeriod;			// Signal arrives from pulse_shapper output 
	double symbolPeriod  = inputSignals[0]->symbolPeriod;

	double sampingPeriod = inputSignals[1]->samplingPeriod;			// Signal arrives from RF_Osclillator output
	double symbolPeriod  = inputSignals[1]->symbolPeriod;
}


bool mixer::runBlock(void)
{

}

