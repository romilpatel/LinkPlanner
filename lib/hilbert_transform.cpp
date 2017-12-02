#include "netxpto.h"
#include "hilbert_transform.h"



using namespace std;

void HilbertTransform::initialize(void)
{
	outputSignals[0]->symbolPeriod = inputSignals[0]->symbolPeriod;
	outputSignals[0]->samplingPeriod = inputSignals[0]->samplingPeriod;
	outputSignals[0]->samplesPerSymbol = inputSignals[0]->samplesPerSymbol;
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());
}

bool HilbertTransform::runBlock(void)
{

	int ready = inputSignals[0]->ready();
	int space = outputSignals[0]->space();
	int process = min(ready, space);

	if (process <= 0) return false;

	t_real S8;
	vector<double> inputBufferTimeDomain(process);
	vector <complex<double>> inputSignalFreqencyDomain(process);
	
	vector <complex<double>> outputSignalsFreq;
	
	for (int i = 0; i < process; i++)									// Get the Input signal as a vector of size "n"
	{
		inputSignals[0]->bufferGet(&S8);
		inputBufferTimeDomain.at(i)=S8;
	}
	
	/*Here we have to convert the vector of REAL value into COMPLEX value because our function acccepts only complex value*/



	inputSignalFreqencyDomain = transform(inputBufferTimeDomain,1);



	//inputSignalsFreq = transform(inputBufferTimeDomain,1);						// Frequeny domain input signal

	/////////// Hilbert Tranformation  //////////////
	// Negative frequency components multiplied by "i" 
	// Positive frequency components multiplied by "-i" 
	// For DC, it's multiplied by "0" 
	// Frequency to time domain conversion
	return true;
	}




