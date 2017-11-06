# include "netxpto.h"
# include "RF_Oscillator.h"

# include <algorithm>
# include <complex>
# include <iostream>
# include <fstream>
# include <random>

using namespace std;


void RFOscillator::initialize(void) {

	outputSignals[0]->setSamplingPeriod(samplingPeriod);
	outputSignals[0]->setSymbolPeriod(symbolPeriod);
	outputSignals[0]->setCentralFrequency(getrfFrequency());
}


bool RFOscillator::runBlock(void) {

	int process = outputSignals[0]->space();

	if (process == 0) return false;

	//t_complex outAverage(cos(phase), sin(phase));
	t_complex out(cos(rfPhase), sin(rfPhase));
	double outrfAmplitude = rfAmplitude;
	double Frequency = outputSignals[0]->getCentralrfFrequency();
	double deltaPhase = sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (2 * outrfAmplitude*samplingPeriod*Frequency));
	double dt = outputSignals[0]->getSamplingPeriod();


	normal_distribution<double> distribution(0, 1);

	out = .5*sqrt(outrfAmplitude)*out;

	for (int i = 0; i < process; i++) {
		if (signaltoNoiseRatio != 0)
		{
			t_real noise = distribution(generatorRIN);
			outrfAmplitude = rfAmplitude + rfAmplitude / signaltoNoiseRatio*noise;
			out = .5*sqrt(outrfAmplitude)*out;
		}
		outputSignals[0]->bufferPut((t_complex)out);
	}

	return true;
}