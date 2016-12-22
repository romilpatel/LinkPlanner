# include <algorithm>
# include <complex>
# include <iostream>
# include <fstream>
# include <random>

# include "netxpto.h"
# include "local_oscillator.h"

using namespace std;


void LocalOscillator::initialize(void){
	
	outputSignals[0]->setSamplingPeriod(samplingPeriod);
	outputSignals[0]->setCentralWavelength(wavelength);
	outputSignals[0]->setCentralFrequency(frequency);
}


bool LocalOscillator::runBlock(void){


    normal_distribution<double> distribution(0, 1);

	t_real dt = inputSignals[0]->getSamplingPeriod();
	t_real wvlgth = inputSignals[0]->getCentralWavelength();
	t_real noisesignal;
	t_real noiselo;

	int process = outputSignals[0]->space();
	
	if (process == 0) return false;

	t_real real = cos(phase);
	t_real imag = sin(phase);
	t_complex lo(real, imag);
	t_real powerlo = opticalPower;

	t_complex out = lo;

	for (int i = 0; i < process; i++) {


		noisesignal = distribution(generator1);
		noiselo = distribution(generator2);

		t_complex loout;

        if (shotNoise) {
            t_real powerlooutsqrted = sqrt(powerlo) + sqrt(PLANCK_CONSTANT*SPEED_OF_LIGHT / (dt * wvlgth))*noiselo*1/2;
            out = .5*powerlooutsqrted*lo;
        } 
		
		outputSignals[0]->bufferPut((t_complex) out);

	}
	return true;
}
