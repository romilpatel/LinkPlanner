<<<<<<< HEAD
=======
# include "netxpto.h"
# include "local_oscillator.h"

>>>>>>> dc00d875a4698894f7854fe56be177086bf2b48b
# include <algorithm>
# include <complex>
# include <iostream>
# include <fstream>
# include <random>

<<<<<<< HEAD
# include "netxpto.h"
# include "local_oscillator.h"

=======
>>>>>>> dc00d875a4698894f7854fe56be177086bf2b48b
using namespace std;


void LocalOscillator::initialize(void){
<<<<<<< HEAD
	
	outputSignals[0]->setSamplingPeriod(samplingPeriod);
	outputSignals[0]->setCentralWavelength(wavelength);
	outputSignals[0]->setCentralFrequency(frequency);
=======

	outputSignals[0]->setSamplingPeriod(samplingPeriod);
	outputSignals[0]->setSymbolPeriod(symbolPeriod);
	outputSignals[0]->setCentralWavelength(wavelength);
	outputSignals[0]->setCentralFrequency(frequency);

>>>>>>> dc00d875a4698894f7854fe56be177086bf2b48b
}


bool LocalOscillator::runBlock(void){

<<<<<<< HEAD

    normal_distribution<double> distribution(0, 1);

	t_real dt = inputSignals[0]->getSamplingPeriod();
	t_real wvlgth = inputSignals[0]->getCentralWavelength();
	t_real noisesignal;
	t_real noiselo;

=======
>>>>>>> dc00d875a4698894f7854fe56be177086bf2b48b
	int process = outputSignals[0]->space();
	
	if (process == 0) return false;

<<<<<<< HEAD
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
=======
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

>>>>>>> dc00d875a4698894f7854fe56be177086bf2b48b
	return true;
}
