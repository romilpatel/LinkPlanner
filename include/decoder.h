# ifndef PROGRAM_INCLUDE_DECODER_H_
# define PROGRAM_INCLUDE_DECODER_H_

# include <math.h> /* pow */
# include <vector>
# include "netxpto.h"


// Implements a IQ modulator.
class Decoder : public Block {

	/* State Variables */

	bool firstTime{ true };

public:

	/* Input Parameters */

	double outputOpticalPower{ 1e-3 };
	double outputOpticalWavelength{ 1550e-9 };
	double outputOpticalFrequency{ SPEED_OF_LIGHT / outputOpticalWavelength };
	t_integer m{ 4 };
	vector<t_complex> iqValues;
	vector<int> iqBinaryValues;

	/* Methods */
	Decoder() {};
	Decoder(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig) {};

	void initialize(void);
	bool runBlock(void);

	void setOutputOpticalPower(double outOpticalPower) { outputOpticalPower = outOpticalPower; }
	void setOutputOpticalPower_dBm(double outOpticalPower_dBm) { outputOpticalPower = 1e-3*pow(10, outOpticalPower_dBm / 10); }

	void setOutputOpticalWavelength(double outOpticalWavelength) { outputOpticalWavelength = outOpticalWavelength; outputOpticalFrequency = SPEED_OF_LIGHT / outOpticalWavelength; }
	void setOutputOpticalFrequency(double outOpticalFrequency) { outputOpticalFrequency = outOpticalFrequency; outputOpticalWavelength = outOpticalFrequency / outputOpticalFrequency; }

	void setM(int mValue);


};

# endif
