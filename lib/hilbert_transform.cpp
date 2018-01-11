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

	t_real input;
	vector<double> inputBufferTimeDomain(process);
	vector <complex<double>> IN(process);
	vector <complex<double>> inputSignalFreqencyDomain(process);
	vector <complex<double>> complexOutputSignalTimeDomain(process);
	vector <double> outputSignalTimeDomain(process);

	ComplexMult C;
	//FourierTransform FT;
	FourierTransformA FT;
	vector<double> c(process);
	vector<double> d(process);
	vector<complex<double>> hilbertTransformerFrequencyDomain(process);
	vector<complex<double>> hilbertTransformedFrequencyDomain(process);
	vector<complex<double>> hilbertTransformedTimeDomain(process);
	vector<double> re(process);
	vector<double> im(process);

	///////////// Hilbert transformer in frequency domain ///////////////
	for (int i = 0; i < process; i++)
	{
		if ((i>0) && (i<process / 2))
		{
			c.at(i) = 0;
			d.at(i) = -1;
		}

		if (i >= process / 2)
		{
			c.at(i) = 0;
			d.at(i) = 1;
		}

		if (i == 0)
		{
			c.at(i) = 0;
			d.at(i) = 0;
		}
	}

	hilbertTransformerFrequencyDomain = C.ReImVect2ComplexVector(c, d);	// create complex vector from real and imag data vector of the hilbert transformer

	///////////////////////////////////////////////////////////////////////

	
	for (int i = 0; i < process; i++)					// Get the Input signal as a vector of size "n"
	{
		inputSignals[0]->bufferGet(&input);
		inputBufferTimeDomain.at(i) = input;
	}
						

	for (int i = 0; i < process; i++)
	{
		re[i] = inputBufferTimeDomain.at(i);			// Real part of input
		im[i] = 0;										// Imaginary part which is manipulated as "0"
	}

	IN = C.ReImVect2ComplexVector(re, im);					// Time domain complex form signal

	inputSignalFreqencyDomain = FT.transform(IN, -1);	// Fast Fourier Transform (FFT)

	hilbertTransformedFrequencyDomain = C.complexVectorMultiplication(inputSignalFreqencyDomain, hilbertTransformerFrequencyDomain); // Multiplication of two complex vector

	hilbertTransformedTimeDomain = FT.transform(hilbertTransformedFrequencyDomain, 1);	// Inverse Fast Fourier Transform (IFFT)

	for (int i = 0; i < process; i++)					// Put the data using bufferput

	{
		t_real OUT;
	    OUT = hilbertTransformedTimeDomain[i].real();
		outputSignals[0]->bufferPut((t_real)(OUT));
	}
	
	return true;

}