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

	double outOpticalPower=opticalPower;
	double wavelength = outputSignals[0]->getCentralWavelength();
	double deltaPhase = sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (2 * opticalPower*samplingPeriod*wavelength));


	normal_distribution<double> distribution(0, 1);
	
	double noiseRIN;
	double noisePhase;
	double outPhase=phase;
	
	for (int i = 0; i < process; i++) {
		if (signaltoNoiseRatio != 0)
		{
			noiseRIN = distribution(generatorRIN);
			outOpticalPower = opticalPower + opticalPower/signaltoNoiseRatio*noiseRIN;
		}
		if (phaseNoise != 0)
		{
			noisePhase = distribution(generatorPhas);
			outPhase = phase + noisePhase*deltaPhase;
		}

		t_complex out(cos(outPhase), sin(outPhase));
		out = .5*sqrt(outOpticalPower)*out;

		outputSignals[0]->bufferPut((t_complex)out);
	}

	return true;
}
