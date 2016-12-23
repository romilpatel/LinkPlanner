# ifndef PROGRAM_INCLUDE_LOCAL_OSCILLATOR_H_
# define PROGRAM_INCLUDE_LOCAL_OSCILLATOR_H_

# include "netxpto.h"

# include <complex>
# include <random>
# include <vector>

class LocalOscillator : public Block {

	/* State Variables */


	/* Input Parameters */

	double opticalPower{ 1e-3 };
	double wavelength{ 1550e-9 };
	double frequency{ SPEED_OF_LIGHT / wavelength };
	double phase{ 0 };
	double samplingPeriod{ 0.0 };

	bool shotNoise{ false };

	default_random_engine generator1;
	default_random_engine generator2;

public:

	/* Methods */
	LocalOscillator() {};
	LocalOscillator(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};
	
	void initialize(void);
	bool runBlock(void);

	void setSamplingPeriod(double sPeriod) { samplingPeriod = sPeriod; }
	void setOpticalPower(double oPower) { opticalPower = oPower; }
	void setOpticalPower_dBm(double oPower_dBm) { opticalPower = 1e-3*pow(10, oPower_dBm / 10); }
	void setWavelength(double wlength) { wavelength = wlength; }
	void setPhase(double lOscillatorPhase) { phase= lOscillatorPhase; }
    void setShotNoise(bool sNoise) { shotNoise=sNoise; }


};

#endif 
