# ifndef PROGRAM_INCLUDE_PHOTODIODE_H_
# define PROGRAM_INCLUDE_PHOTODIODE_H_

# include "netxpto.h"
<<<<<<< HEAD
#include <random>
=======
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd

// Simulates a photodiode
class Photodiode : public Block {

	bool firstTime{ true };
	int aux = 0;
	bool firstPass{ true };
	double t = 0;

public:

<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
	double frequencyMismatch{ 1.9441e+11 };
	double responsivity = 1;
	bool shotNoise = false;

	default_random_engine generatorAmp1;
	default_random_engine generatorAmp2;
<<<<<<< HEAD

	Photodiode() {};
	Photodiode(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};
	
=======
=======
	double outputOpticalWavelength{ 1550e-9 };
	double outputOpticalFrequency{ SPEED_OF_LIGHT / outputOpticalWavelength };
	t_real responsivity = 1;
>>>>>>> AnaLuisa

	Photodiode() {};
	Photodiode(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig) {};

>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
	void initialize(void);
	bool runBlock(void);

	void setResponsivity(double Responsivity) { responsivity = Responsivity; }
	double const getResponsivity(void) { return responsivity; }

	void useNoise(bool sNoise) { shotNoise = sNoise; }

private:
};


#endif // !PROGRAM_INCLUDE_PHOTODIODE_H_
