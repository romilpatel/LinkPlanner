# ifndef PROGRAM_INCLUDE_REAL_TO_COMPLEX_H_
# define PROGRAM_INCLUDE_REAL_TO_COMPLEX_H_

# include "netxpto.h"


// Creates a complex signal from two real signals
class realToComplex : public Block {

	/* State Variables */
	bool firstTime{ true };

 public:

	/* Methods */
	realToComplex() {};
	realToComplex(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :
		Block(InputSig, OutputSig){};

	void initialize(void);
	bool runBlock(void);

};

# endif // PROGRAM_INCLUDE_REAL_TO_COMPLEX_H_
