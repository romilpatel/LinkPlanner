# ifndef PROGRAM_INCLUDE_BIT_ERROR_RATE_H_
# define PROGRAM_INCLUDE_BIT_ERROR_RATE_H_

# include "netxpto.h"
# include <vector>

// Calculates the BER between two binary signals
class BitErrorRate : public Block {

	bool firstTime{ true };
	
public:

	t_real z = 1.96;

	BitErrorRate(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig,OutputSig){};
	
	void initialize(void);
	bool runBlock(void);

	long int coincidences = 0;
	long int recievedbits = 0;

	void setZ(t_real Z) { z = Z; }

private:

};


#endif // !PROGRAM_INCLUDE_BIT_ERROR_RATE_H_
