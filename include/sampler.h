# ifndef PROGRAM_INCLUDE_SAMPLER_H_
# define PROGRAM_INCLUDE_SAMPLER_H_

# include "netxpto.h"
# include <vector>

// Takes a sampling of the input electrical signal
class Sampler : public Block {

	bool firstTime{ true };

	int sampling = 16;

	int delay = 9;

	int AuxInt = 0;

	t_integer samplesToSkip{ 0 };


public:

	void initialize(void);
	bool runBlock(void);

	Sampler() {};
	Sampler(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig) {};

	void setSamplingRate(int Sampling) { sampling = Sampling; }
	void setDelay(int Delay) { delay = Delay; }
	void setSamplesToSkip(t_integer sToSkip) { samplesToSkip = sToSkip; }

};


#endif // !PROGRAM_INCLUDE_SAMPLER_H_
