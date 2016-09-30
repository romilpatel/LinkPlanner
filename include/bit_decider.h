# ifndef PROGRAM_INCLUDE_BIT_DECIDER_H_
# define PROGRAM_INCLUDE_BIT_DECIDER_H_

# include "netxpto.h"
# include <vector>

// Evaluates the input signal and outputs a binary key in accordance to the input values
class BitDecider : public Block {

	bool firstTime{ true };

public:

	double bitPeriod{ 1.0 / 50e9 };

	BitDecider(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};
	
	void initialize(void);
	bool runBlock(void);

	void setBitPeriod(double bPeriod);
	double const getBitPeriod(void) { return bitPeriod; }


private:
};


#endif // !PROGRAM_INCLUDE_BIT_DECIDER_H_
