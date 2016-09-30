# ifndef PROGRAM_INCLUDE_BIT_ERROR_RATE_H_
# define PROGRAM_INCLUDE_BIT_ERROR_RATE_H_

# include "netxpto.h"
# include <vector>

// Calculates the BER between two binary signals
class BitErrorRate : public Block {

	bool firstTime{ true };
	
public:

	BitErrorRate(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig,OutputSig){};
	
	void initialize(void);
	bool runBlock(void);

	int coincidences = 0;
	int recievedbits = 0;

private:

};


#endif // !PROGRAM_INCLUDE_BIT_ERROR_RATE_H_
