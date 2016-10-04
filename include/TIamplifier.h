# ifndef PROGRAM_INCLUDE_TIAMPLIFIER_H_
# define PROGRAM_INCLUDE_TIAMPLIFIER_H_

# include "netxpto.h"
# include <vector>

// Simulates a Transimpedance Amplifier
class TIAmplifier : public Block {

	bool firsTime{ true };

public:

	t_real amplification = 1e6;
	t_real noiseamp = 1e-4;

	TIAmplifier(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};
	
	void initialize(void);
	bool runBlock(void);

	void setAmplification(t_real Amplification) { amplification = Amplification; }
	void setNoiseAmplitude(t_real NoiseAmplitude) { noiseamp = NoiseAmplitude; }

private:
};


#endif // !PROGRAM_INCLUDE_TIAMPLIFIER_H_
