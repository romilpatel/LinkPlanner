# ifndef PROGRAM_INCLUDE_BIT_ERROR_RATE_H_
# define PROGRAM_INCLUDE_BIT_ERROR_RATE_H_

# include "netxpto.h"
# include <vector>

// Calculates the BER between two binary signals
class BitErrorRate : public Block {

	bool firstTime{ true };
	
public:

	int firstPass=1;

	t_real alpha = 0.05;
	int m = 0;
	int n = 0;

	BitErrorRate(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig,OutputSig){};
	
	void initialize(void);
	bool runBlock(void);

	long int coincidences = 0;
	long int recievedbits = 0;

	void setConfidence(t_real P) { alpha = 1-P; }
	void setMidReportSize(t_real M) { m = M; }

private:

};


#endif // !PROGRAM_INCLUDE_BIT_ERROR_RATE_H_
