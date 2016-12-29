# ifndef PROGRAM_INCLUDE_IDEAL_AMPLIFIER_H_
# define PROGRAM_INCLUDE_IDEAL_AMPLIFIER_H_

# include "netxpto.h"
# include <vector>
#include <random>

// Simulates a Transimpedance Amplifier
class IdealAmplifier : public Block {

	bool firsTime{ true };

public:

	t_real amplification = 1e4;	

	IdealAmplifier() {};
	IdealAmplifier(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};
	
	void initialize(void);
	bool runBlock(void);

	void setAmplification(t_real Amplification) { amplification = Amplification; }

private:
};


#endif // !PROGRAM_INCLUDE_TIAMPLIFIER_H_
