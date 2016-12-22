# ifndef PROGRAM_INCLUDE_LOCAL_OSCILLATOR_H_
# define PROGRAM_INCLUDE_LOCAL_OSCILLATOR_H_

#include <complex>
#include <random>
# include <vector>

# include "netxpto.h"


class LocalOscillator : public Block {

	/* State Variables */

	bool firstTime{ true };

public:

	/* Input Parameters */

	double outputOpticalPower{ 1e-3 };
	double outputOpticalWavelength{ 1550e-9 };
	double outputOpticalFrequency{ SPEED_OF_LIGHT / outputOpticalWavelength };
	double localOscillatorPhase{ 0 };
	double samplingPeriod{ 0.0 };
    
    bool shotNoise{false};

	//t_real h = 6.62607004e-34;
	
	/* Methods */
	LocalOscillator() {};
	LocalOscillator(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};
	
	void initialize(void);
	bool runBlock(void);

	void setSamplingPeriod(double sPeriod) { samplingPeriod = sPeriod; }
	void setLocalOscillatorOpticalPower(double outOpticalPower) { outputOpticalPower = outOpticalPower; }
	void setLocalOscillatorOpticalPower_dBm(double outOpticalPower_dBm) { outputOpticalPower = 1e-3*pow(10, outOpticalPower_dBm / 10); }
	void setLocalOscillatorPhase(double lOscillatorPhase) { localOscillatorPhase= lOscillatorPhase; }
    void setShotNoise(bool sNoise) { shotNoise=sNoise; }

private:

	default_random_engine generator1;
	default_random_engine generator2;

};

#endif // !PROGRAM_INCLUDE_LOCAL_OSCILLATOR_H_
