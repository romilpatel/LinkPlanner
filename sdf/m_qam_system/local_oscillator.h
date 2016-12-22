# ifndef PROGRAM_INCLUDE_LOCAL_OSCILLATOR_H_
# define PROGRAM_INCLUDE_LOCAL_OSCILLATOR_H_

#include <complex>

# include "netxpto.h"
# include <vector>

class LocalOscillator : public Block {
	bool firstTime{ true };

public:

	double outputOpticalPower{ 1e-3 };
	double outputOpticalWavelength{ 1550e-9 };
	double outputOpticalFrequency{ SPEED_OF_LIGHT / outputOpticalWavelength };
	double LocalOscillatorPhase = 0;


	LocalOscillator(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig) {};

	void initialize(void);
	bool runBlock(void);

	void setLocalOscillatorOpticalPower(double outOpticalPower) { outputOpticalPower = outOpticalPower; }
	void setLocalOscillatorOpticalPower_dBm(double outOpticalPower_dBm) { outputOpticalPower = 1e-3*pow(10, outOpticalPower_dBm / 10); }
	void setLocalOscillatorPhase(double LOPhase) { LocalOscillatorPhase = LOPhase; }

private:
};


#endif // !PROGRAM_INCLUDE_LOCAL_OSCILLATOR_H_