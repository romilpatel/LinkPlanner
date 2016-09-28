# ifndef PROGRAM_INCLUDE_TESTBLOCK_H_
# define PROGRAM_INCLUDE_TESTBLOCK_H_

# include "netxpto.h"
# include <vector>

// this is a test block for the purpose of beta testing new code
// current code: TIAMP with electrical noise
class testblock : public Block {

	bool firstTime{ true };

public:

	testblock(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig,OutputSig){};
	
	void initialize(void);
	bool runBlock(void);

private:

};


#endif // !PROGRAM_INCLUDE_DISCRETIZER_H_
