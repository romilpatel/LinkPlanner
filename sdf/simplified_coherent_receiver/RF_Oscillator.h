# ifndef PROGRAM_INCLUDE_RF_OSCILLATOR_H_
# define PROGRAM_INCLUDE_RF_OSCILLATOR_H_


# include "netxpto.h"

# include <complex>
# include <random>
# include <vector>

class RFOscillator : public Block {

	/* State Variables */


	/* Input Parameters */

	double rfAmplitude{ 1.0 };				
	double rfPhase{ 0.0 };
	double rfFrequency{ 100E6 };

	/*double opticalPower{ 1e-3 };
	double outputOpticalWavelength{ 1550e-9 };
	double outputOpticalFrequency{ SPEED_OF_LIGHT / outputOpticalWavelength };
	double phase{ 0 };*/

	double samplingPeriod{ 0.0 };
	double symbolPeriod{ 0.0 };

	default_random_engine generatorRIN;
	double signaltoNoiseRatio{ 0 };

public:

	/* Methods */
	RFOscillator() {};
	RFOscillator(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) : Block(InputSig, OutputSig) {};

	void initialize(void);
	bool runBlock(void);

	void setSamplingPeriod(double sPeriod) { samplingPeriod = sPeriod; }					// ? How it works?
	void setSymbolPeriod(double sPeriod) { symbolPeriod = sPeriod; }
	
	void setrfAmplitude(double rfAmpl) { rfAmplitude = rfAmpl; }							// Set Amplitude of the RF Oscillator
	double getrfAmplitude() { return rfAmplitude; }

	void setrfFrequency(double rfFreq) { rfFrequency = rfFreq; }							// Set Frequency of the RF Oscillator
	double getrfFrequency() { return rfFrequency; }

	void setrfPhase(double rfPh) { rfPhase = rfPh; }										// Set Phase     of the RF Oscillator
	double getrfPhase() { return rfPhase; }
	
	void setSignaltoNoiseRatio(double sNoiseRatio) { signaltoNoiseRatio = sNoiseRatio; }	// Signal to noise ratio
	double const getSignaltoNoiseRatio(void) { return signaltoNoiseRatio; }

};

#endif 
