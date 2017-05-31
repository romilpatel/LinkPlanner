#include <algorithm>
#include <complex>
#include <random>
#include <fstream>
#include <iostream>

#include "netxpto.h"
#include "white_noise.h"


void WhiteNoise::initialize(void){

	firsTime = false;

//	outputSignals[0]->setSamplingPeriod(samplingPeriod);
//	outputSignals[0]->setSymbolPeriod(symbolPeriod);

}


bool WhiteNoise::runBlock(void){



	int space = outputSignals[0]->space();

	int process = space;

	if (process == 0) return false;
	
	signal_value_type sType = outputSignals[0]->getValueType();
	switch (sType)
	{
	case ComplexValue:
	{
						 normal_distribution<double> distributionNoiseI(0, 1);
						 normal_distribution<double> distributionNoiseQ(0, 1);
						 for (int i = 0; i < process; i++) {

							 t_complex output(0, 0);

							 if (spectralDensity != 0)
							 {
								 t_real noiseI = distributionNoiseI(generator1);
								 t_real noiseQ = distributionNoiseQ(generator2);
								 output = (noiseI*spectralDensity / sqrt(2), noiseQ*spectralDensity / sqrt(2));
							 }

							 outputSignals[0]->bufferPut(output);
						 }

						 break;
	}
	case ComplexValueXY:
	{
						   normal_distribution<double> distributionNoiseIX(0, 1);
						   normal_distribution<double> distributionNoiseQX(0, 1);
						   normal_distribution<double> distributionNoiseIY(0, 1);
						   normal_distribution<double> distributionNoiseQY(0, 1);

						   for (int i = 0; i < process; i++) {

							   t_complex_xy output = { 0, 0 };

							   if (spectralDensity != 0)
							   {
								   t_real noiseIX = distributionNoiseIX(generator1);
								   t_real noiseQX = distributionNoiseQX(generator2);
								   output.x = (noiseIX*spectralDensity / sqrt(2), noiseQX*spectralDensity / sqrt(2));
								   t_real noiseIY = distributionNoiseIY(generator3);
								   t_real noiseQY = distributionNoiseQY(generator4);
								   output.y = (noiseIY*spectralDensity / sqrt(2), noiseQY*spectralDensity / sqrt(2));

							   }

							   outputSignals[0]->bufferPut(output);
						   }
						   break;
	}
	}
	
	return true;
}