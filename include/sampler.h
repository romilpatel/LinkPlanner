# ifndef PROGRAM_INCLUDE_SAMPLER_H_
# define PROGRAM_INCLUDE_SAMPLER_H_

# include "netxpto.h"
# include <vector>

// Takes a sampling of the input electrical signal
class Sampler : public Block {

	bool firstTime{ true };

	t_integer samplesToSkip{ 0 };

public:

	Sampler() {};
	Sampler(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};

	void initialize(void);
	bool runBlock(void);

	void setSamplesToSkip(int sToSkip) { samplesToSkip = sToSkip; }
	int const getSamplesToSkip(void) { return samplesToSkip; }

};


#endif // !PROGRAM_INCLUDE_SAMPLER_H_
