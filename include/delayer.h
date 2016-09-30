# ifndef PROGRAM_INCLUDE_DELAYER_H_
# define PROGRAM_INCLUDE_DELAYER_H_

# include "netxpto.h"
# include <vector>

// Adjusts the starting point of the discretized signal
class Delayer : public Block {

	bool firstTime{ true };

public:

	Delayer(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};
	int auxint = 0;
	

	void initialize(void);
	bool runBlock(void);
private:
};


#endif // !PROGRAM_INCLUDE_DISCRETIZER_H_
