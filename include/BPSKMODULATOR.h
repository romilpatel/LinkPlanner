# ifndef PROGRAM_INCLUDE_BPSKMODULATOR_H_
# define PROGRAM_INCLUDE_BPSKMODULATOR_H_

# include <math.h>       /* pow */
# include "netxpto.h"

// Changes the IQ modulator.
class BPSKMODULATOR : public Block {

	/* State Variables */

	bool firstTime{ true };

public:

	/* Input Parameters */

	double outputOpticalPower{ 1e-3 };
	double outputOpticalWavelength{ 1550e-9 };
	double outputOpticalFrequency{ SPEED_OF_LIGHT / outputOpticalWavelength };

	/* Methods */

	BPSKMODULATOR(vector<Signal *> &InputSig, vector<Signal *> &OutputSig);
	bool runBlock(void);
	
	void setOutputOpticalPower(double outOpticalPower) { outputOpticalPower = outOpticalPower; }
	void setOutputOpticalPower_dBm(double outOpticalPower_dBm) { outputOpticalPower = 1e-3*pow(10, outOpticalPower_dBm / 10); }

	void setOutputOpticalWavelength(double outOpticalWavelength) { outputOpticalWavelength = outOpticalWavelength; outputOpticalFrequency = SPEED_OF_LIGHT / outOpticalWavelength; }
	void setOutputOpticalFrequency(double outOpticalFrequency) { outputOpticalFrequency = outOpticalFrequency; outputOpticalWavelength = outOpticalFrequency / outputOpticalFrequency; }
};

# endif 
