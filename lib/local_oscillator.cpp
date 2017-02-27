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

	t_complex out(cos(phase), sin(phase));
	out= .5*sqrt(opticalPower)*out;

	for (int i = 0; i < process; i++) {

        /*if (shotNoise) {
			t_complex loout;

			normal_distribution<double> distribution(0, 1);

			t_real dt = outputSignals[0]->getSamplingPeriod();
			t_real wvlgth = outputSignals[0]->getCentralWavelength();
			t_real noisesignal;
			t_real noiselo;

			noisesignal = distribution(generator1);
			noiselo = distribution(generator2);

            t_real powerlooutsqrted = sqrt(powerlo) + sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (dt * wvlgth))*noiselo*1/2;
            out = .5*powerlooutsqrted*lo;
        }*/ 
		
		outputSignals[0]->bufferPut((t_complex)out);
	}

	return true;
}
