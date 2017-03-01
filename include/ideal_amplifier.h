# ifndef PROGRAM_INCLUDE_IDEAL_AMPLIFIER_H_
# define PROGRAM_INCLUDE_IDEAL_AMPLIFIER_H_

# include "netxpto.h"
# include <vector>
#include <random>

// Simulates a Transimpedance Amplifier
class IdealAmplifier : public Block {

	double gain{ 1e4 };

public:

<<<<<<< HEAD
=======
	double gain = 1e4;	

>>>>>>> 14adca355faa92683b01e2a95152ddb168447487
	IdealAmplifier() {};
	IdealAmplifier(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};
	
	void initialize(void);
	bool runBlock(void);

<<<<<<< HEAD
	void setGain(double ga) { gain = ga; }
	double getGain() { return gain; }
=======
	void setGain(t_real Gain) { gain = Gain; }
>>>>>>> 14adca355faa92683b01e2a95152ddb168447487

};


#endif // !PROGRAM_INCLUDE_TIAMPLIFIER_H_
