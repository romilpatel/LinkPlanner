# ifndef PROGRAM_INCLUDE_BIT_DECIDER_H_
# define PROGRAM_INCLUDE_BIT_DECIDER_H_

# include "netxpto.h"
# include <vector>

// Evaluates the input signal and outputs a binary key in accordance to the input values
class bit_decider : public Block {

	bool firstTime{ true };

public:

	bit_decider(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};
	
	void initialize(void);
	bool runBlock(void);

private:
};


#endif // !PROGRAM_INCLUDE_BIT_DECIDER_H_
