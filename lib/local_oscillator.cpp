# include "netxpto.h"
# include "local_oscillator.h"

# include <algorithm>
# include <complex>
# include <iostream>
# include <fstream>
# include <random>

using namespace std;


void LocalOscillator::initialize(void){

	outputSignals[0]->setSamplingPeriod(samplingPeriod);
	outputSignals[0]->setSymbolPeriod(symbolPeriod);
	outputSignals[0]->setCentralWavelength(wavelength);
	outputSignals[0]->setCentralFrequency(frequency);

}


bool LocalOscillator::runBlock(void){

	int process = outputSignals[0]->space();
	
	if (process == 0) return false;

	t_complex outAverage(cos(phase), sin(phase));
	t_complex out;
	double outOpticalPower=opticalPower;
	out= .5*sqrt(opticalPower)*out;

	normal_distribution<double> distributionNoise(0, 1);
	for (int i = 0; i < process; i++) {
		if (signaltoNoiseRatio != 0)
		{
			t_real noise = distributionNoise(generator);
			outOpticalPower = opticalPower + opticalPower/signaltoNoiseRatio*noise;
		}
		out = .5*sqrt(outOpticalPower)*outAverage;
		outputSignals[0]->bufferPut((t_complex)out);
	}

	return true;
}
