# ifndef PROGRAM_INCLUDE_TESTBLOCK_H_
# define PROGRAM_INCLUDE_TESTBLOCK_H_

# include "netxpto.h"
# include <vector>
# include <array>


// this is a test block for the purpose of beta testing new code
// current code: Studying the BER discrepency.
class testblock : public Block {

	bool firstTime{ true };

public:

	double outputOpticalPower{ 1e-3 };
	double outputOpticalWavelength{ 1550e-9 };
	double outputOpticalFrequency{ SPEED_OF_LIGHT / outputOpticalWavelength };

	//array <t_real, 161129> translator;
	//long int index = 0;

	testblock(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig,OutputSig){};
	
	void initialize(void);
	bool runBlock(void);

	

private:

};


#endif // !PROGRAM_INCLUDE_DISCRETIZER_H_
