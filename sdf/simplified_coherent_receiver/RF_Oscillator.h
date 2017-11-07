# ifndef PROGRAM_INCLUDE_RF_OSCILLATOR_H_
# define PROGRAM_INCLUDE_RF_OSCILLATOR_H_


# include "netxpto.h"

# include <complex>
# include <random>
# include <vector>

class RfOscillator : public Block {

	/* Input Parameters */

	double rfAmplitude{ 1.0 };				
	double rfInitialPhase{ 0.0 };
	double rfFrequency{ 100E6 };

	/*double opticalPower{ 1e-3 };
	double outputOpticalWavelength{ 1550e-9 };
	double outputOpticalFrequency{ SPEED_OF_LIGHT / outputOpticalWavelength };
	double phase{ 0 };*/

	double samplingPeriod{ 1.0 };

	/* State Variables */
	double phase{ rfInitialPhase };

public:

	/* Methods */
	RfOscillator() {};
	RfOscillator(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) : Block(InputSig, OutputSig) {};

	void initialize(void);
	bool runBlock(void);

	void setSamplingPeriod(double sPeriod) { samplingPeriod = sPeriod; }					// ? How it works?
	
	void setRfAmplitude(double rfAmpl) { rfAmplitude = rfAmpl; }							// Set Amplitude of the RF Oscillator
	double getRfAmplitude() { return rfAmplitude; }

	void setRfFrequency(double rfFreq) { rfFrequency = rfFreq; }							// Set Frequency of the RF Oscillator
	double getRfFrequency() { return rfFrequency; }

	void setRfPhase(double rfPh) { rfInitialPhase = rfPh; }										// Set Phase     of the RF Oscillator
	double getRfPhase() { return rfInitialPhase; }
	
};

#endif 
