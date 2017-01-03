# ifndef PROGRAM_INCLUDE_SAMPLER_H_
# define PROGRAM_INCLUDE_SAMPLER_H_

# include "netxpto.h"
# include <vector>

// Takes a sampling of the input electrical signal
class Sampler : public Block {

	bool firstTime{ true };

<<<<<<< HEAD
public:

	int sampling = 16;

	int delay = 9;
=======
	t_integer samplesToSkip{ 0 };

public:
>>>>>>> dc00d875a4698894f7854fe56be177086bf2b48b

	Sampler() {};
	Sampler(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};

	void initialize(void);
	bool runBlock(void);

<<<<<<< HEAD
	void setSamplingRate(int Sampling) { sampling = Sampling; }
	void setDelay(int Delay) { delay = Delay; }
	void setSamplesToSkip(t_integer sToSkip) { samplesToSkip = sToSkip; }

private:

	int AuxInt = 0;

	t_integer samplesToSkip{ 0 };

=======
	void setSamplesToSkip(t_integer sToSkip) { samplesToSkip = sToSkip; }

>>>>>>> dc00d875a4698894f7854fe56be177086bf2b48b
};


#endif // !PROGRAM_INCLUDE_SAMPLER_H_
