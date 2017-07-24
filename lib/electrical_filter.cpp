#include <algorithm>
#include <complex>
#include <array>
#include <vector>

#include "netxpto.h"
#include "electrical_filter.h"

using namespace std;

void raisedCosine1(vector<t_real> &impulseResponse, int impulseResponseLength, double rollOffFactor, double samplingPeriod, double symbolPeriod);

void ElectricalFilter::initialize(void){

	double samplingPeriod = inputSignals[0]->samplingPeriod;
	double symbolPeriod = inputSignals[0]->symbolPeriod;

	impulseResponseLength = (int)floor(impulseResponseTimeLength*symbolPeriod / samplingPeriod);
	
	impulseResponse.resize(impulseResponseLength);

	switch (getFilterType()) {

	case RaisedCosine1:
			raisedCosine1(impulseResponse, impulseResponseLength, rollOffFactor, samplingPeriod, symbolPeriod);
			break;
	};

	initializeFIR_Filter();

}

void raisedCosine1(vector<t_real> &impulseResponse, int impulseResponseLength, double rollOffFactor, double samplingPeriod, double symbolPeriod) {
	double sinc;
	for (int i = 0; i < impulseResponseLength; i++)
	{
		t_real t = -impulseResponseLength / 2 * samplingPeriod + i*samplingPeriod;
		if (t!=0)
		{
			sinc = sin(PI*t / symbolPeriod) / (PI*t / symbolPeriod);

		}
		else
		{
			sinc = 1;
		}
		impulseResponse[i] = sinc*cos(rollOffFactor*PI*t / symbolPeriod) / (1 - (4.0*rollOffFactor*rollOffFactor*t*t) / (symbolPeriod*symbolPeriod));
	};
};

/*bool ElectricalFilter::runBlock(void){
	int ready = inputSignals[0]->ready();
	int space = outputSignals[0]->space();
	int process = min(ready, space);
	t_real sampling;
	sampling=inputSignals[0]->getSamplingPeriod();
	t_real SymbolPeriod;
	SymbolPeriod = inputSignals[0]->getSymbolPeriod();
	


	t_real in;
	vector<t_real> In(ready);
	vector<t_complex> Out(ready);
	t_real out;


	if (process == 0) return false;


	for (int i = 0; i < ready; i++) {

		
		inputSignals[0]->bufferGet(&in);
		In[i] = in;

	}

	vector <t_complex> FFTIn(ready);
	vector <t_complex> FFTaux1(ready);
	t_complex imaginary(0, 1);
	t_real Ready = ready;
	t_real length = 16;
	vector <t_real> h(length);
	vector <t_complex> hfft(ready);

	for (int i = 0; i < sizeof(h); i++)
	{
		t_real t = -length / 2 * sampling + i*sampling;
		if (t != 0)
			{
			h[i] = sin(PI*t / SymbolPeriod) / (PI*t / SymbolPeriod);
		}
		else
		{
			h[i] = 1;
		}
	}

	
	for (int i = 0; i < ready; i++)
	{
		t_real I = i;
		FFTIn[i] = 0;
		hfft[i] = 0;
		for (int k = 0; k < ready; k++)
		{
			t_real K = k;
			FFTIn[i] = FFTIn[i]+In[k] * exp(imaginary*2.0*PI*K*I / Ready);
		}
		for (int u = 0; u < length; u++)
		{
			t_real U = u;
			hfft[i] = hfft[i] + h[u] * exp(imaginary*2.0*PI*U*I / Ready);
		}
		FFTaux1[i] = FFTIn[i] * hfft[i];
	}

	for (int i = 0; i < ready; i++)
	{
		t_real I = i;
		Out[i] = 0;
		for (int k = 0; k <ready; k++)
		{
			t_real K = k;
			Out[i] = Out[i] + FFTaux1[k] * exp(imaginary*2.0*PI*K*I / Ready);
		}
		out = real(Out[i]);
		outputSignals[0]->bufferPut(out);
	}

}*/