# ifndef PROGRAM_INCLUDE_PHOTODIODE_H_
# define PROGRAM_INCLUDE_PHOTODIODE_H_

# include "netxpto.h"

// Simulates a photodiode
class Photodiode : public Block {

	bool firstTime{ true };

public:

	double outputOpticalWavelength{ 1550e-9 };
	double outputOpticalFrequency{ SPEED_OF_LIGHT / outputOpticalWavelength };
	t_real responsivity = 1;

	Photodiode() {};
	Photodiode(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig) {};

	void initialize(void);
	bool runBlock(void);

	void  setResponsivity(t_real Responsivity) { responsivity = Responsivity; }

private:
};


#endif // !PROGRAM_INCLUDE_PHOTODIODE_H_
