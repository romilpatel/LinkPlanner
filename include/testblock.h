# ifndef PROGRAM_INCLUDE_TESTBLOCK_H_
# define PROGRAM_INCLUDE_TESTBLOCK_H_

# include "netxpto.h"
# include <vector>

// this is a test block for the purpose of beta testing new code
// current code: BER
class testblock : public Block {
public:
	testblock(vector<Signal *> &InputSig, vector<Signal *> &OutputSig);
	bool runBlock(void);

	int coincidences = 0;
	int recievedbits = 0;


	//int index = 0;

//	int setindex(int index);



private:





};


#endif // !PROGRAM_INCLUDE_DISCRETIZER_H_
