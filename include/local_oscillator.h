# ifndef PROGRAM_INCLUDE_LOCAL_OSCILLATOR_H_
# define PROGRAM_INCLUDE_LOCAL_OSCILLATOR_H_

#include <complex>

# include "netxpto.h"
# include <vector>

// this is a test block for the purpose of beta testing new code
// current code: BER
class LocalOscillator : public Block {

	/* State Variables */

	bool firstTime{ true };

public:

	/* Input Parameters */

	double outputOpticalPower{ 1e-3 };
	double outputOpticalWavelength{ 1550e-9 };
	double outputOpticalFrequency{ SPEED_OF_LIGHT / outputOpticalWavelength };
	double LocalOscillatorPhase = 0;

	/* Methods */
	LocalOscillator() {};
	LocalOscillator(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};
	
	void initialize(void);
	bool runBlock(void);

	void setLocalOscillatorOpticalPower(double outOpticalPower) { outputOpticalPower = outOpticalPower; }
	void setLocalOscillatorOpticalPower_dBm(double outOpticalPower_dBm) { outputOpticalPower = 1e-3*pow(10, outOpticalPower_dBm / 10); }
	void setLocalOscillatorPhase(double LOPhase) { LocalOscillatorPhase= LOPhase; }

};

#endif // !PROGRAM_INCLUDE_LOCAL_OSCILLATOR_H_
