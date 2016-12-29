#include <algorithm>
#include <complex>
#include <random>
#include <fstream>
#include <iostream>

#include "netxpto.h"
#include "white_noise.h"


void WhiteNoise::initialize(void){

	firsTime = false;

	outputSignals[0]->setSamplingPeriod(samplingPeriod);
	outputSignals[0]->setSymbolPeriod(symbolPeriod);

}


bool WhiteNoise::runBlock(void){

	normal_distribution<double> distributionNoiseI(noisebias, noiseamp/2);
	normal_distribution<double> distributionNoiseQ(noisebias, noiseamp/2);

	int space = outputSignals[0]->space();

	int process = space;

	if (process == 0) return false;
	for (int i = 0; i < process; i++) {
		
		t_real noiseI = distributionNoiseI(generator1);
		t_real noiseQ = distributionNoiseQ(generator2);
		t_complex output(noiseI, noiseQ);
		
		outputSignals[0]->bufferPut(output);
	}
	return true;
}