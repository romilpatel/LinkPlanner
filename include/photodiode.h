# ifndef PROGRAM_INCLUDE_PHOTODIODE_H_
# define PROGRAM_INCLUDE_PHOTODIODE_H_

# include "netxpto.h"
#include <random>

// Simulates a photodiode
class Photodiode : public Block {

	bool firstTime{ true };

public:

	double outputOpticalWavelength{ 1550e-9 };
	double outputOpticalFrequency{ SPEED_OF_LIGHT / outputOpticalWavelength };
	double responsivity = 1;
	bool shotNoise = false;

	default_random_engine generator1I;
	default_random_engine generator1Q;
	default_random_engine generator2I;
	default_random_engine generator2Q;

	Photodiode() {};
	Photodiode(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};
	
	void initialize(void);
	bool runBlock(void);

	void setResponsivity(double Responsivity) { responsivity = Responsivity; }
	double const getResponsivity(void) { return responsivity; }

	void useNoise(bool sNoise) { shotNoise = sNoise; }

private:
};


#endif // !PROGRAM_INCLUDE_PHOTODIODE_H_
