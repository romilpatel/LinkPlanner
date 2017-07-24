# ifndef PROGRAM_INCLUDE_PHASESHIFTER_H_
# define PROGRAM_INCLUDE_PHASESHIFTER_H_

# include "netxpto.h"

// Introduces a 90 degree phase sift in the signal
class phaseShifter : public Block {

	bool firstTime{ true };

public:

	double outputOpticalWavelength{ 1550e-9 };
	double outputOpticalFrequency{ SPEED_OF_LIGHT / outputOpticalWavelength };

	phaseShifter(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig) {};

	void initialize(void);
	bool runBlock(void);


private:
};


#endif 
