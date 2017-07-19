# ifndef PROGRAM_INCLUDE_PIN_H_
# define PROGRAM_INCLUDE_PIN_H_

# include <math.h>       /* pow */
# include "netxpto.h"


// Implements a Pin.
class Pin : public Block {

	/* State Variables */

	//bool firstTime{ true };

public:

	/* Input Parameters */

	double responsivity{ 1.0 }; //responsivity
	
	/* Methods */
	Pin() {}; //nao sei
	Pin(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig) {}; //nao sei

	void initialize(void); //?
	bool runBlock(void); //?


	void setResposivity(double resp) { responsivity = resp; } 
	
};

# endif // PROGRAM_INCLUDE_netxpto_H_

