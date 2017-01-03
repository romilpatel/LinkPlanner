# ifndef PROGRAM_INCLUDE_SUBTRACTOR_H_
# define PROGRAM_INCLUDE_SUBTRACTOR_H_

# include "netxpto.h"

<<<<<<< HEAD
// Simulates a current subtractor
=======
// Simulates a subtractor
>>>>>>> dc00d875a4698894f7854fe56be177086bf2b48b
class Subtractor : public Block {

	bool firstTime{ true };

public:

	double outputOpticalPower{ 1e-3 };
	double outputOpticalWavelength{ 1550e-9 };
	double outputOpticalFrequency{ SPEED_OF_LIGHT / outputOpticalWavelength };

<<<<<<< HEAD
	Subtractor(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig) {};

	void initialize(void);
	bool runBlock(void);

=======
	Subtractor() {};
	Subtractor(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};
	
	void initialize(void);
	bool runBlock(void);
	
>>>>>>> dc00d875a4698894f7854fe56be177086bf2b48b
private:
};


#endif // !PROGRAM_INCLUDE_SUBTRACTOR_H_
<<<<<<< HEAD

=======
>>>>>>> dc00d875a4698894f7854fe56be177086bf2b48b
