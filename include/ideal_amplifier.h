# ifndef PROGRAM_INCLUDE_IDEAL_AMPLIFIER_H_
# define PROGRAM_INCLUDE_IDEAL_AMPLIFIER_H_

# include <math.h>       /* pow */
# include "netxpto.h"


// Implements an amplifier.
class IdealAmplifier : public Block {

	/* State Variables */

	

 public:

	 /* Input Parameters */

	 double gain{ 1 };
	 double gain_dB{ 0 };

	 /* Methods */
	 IdealAmplifier() {};
	 IdealAmplifier(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};

	 void initialize(void);
	 bool runBlock(void);

	 void setGain(double g) { gain = g; gain_dB = 10 * log10(gain); }
	 double getGain() { return gain; }

	 void setGain_dB(double g_dB) { gain_dB = g_dB; gain = pow(10.0,g_dB/10); }
	 double getGain_dB() { return gain_dB; }
	 
};

# endif 


