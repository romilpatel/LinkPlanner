# ifndef CLOCK_H_
# define CLOCK_H_

# include "netxpto.h"

class Clock : public Block {

	double wavelength{ 1550e-9 };
	double frequency{ SPEED_OF_LIGHT / wavelength };
	double samplingPeriod{ 0.0 };

public:

	Clock() {};
	Clock(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig) {};

	void initialize(void);
	bool runBlock(void);

	void setSamplingPeriod(double sPeriod) { samplingPeriod = sPeriod; }

};

# endif
