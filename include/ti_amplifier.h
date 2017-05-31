# ifndef PROGRAM_INCLUDE_TIAMPLIFIER_H_
# define PROGRAM_INCLUDE_TIAMPLIFIER_H_

# include "netxpto.h"
# include <vector>
#include <random>

// Simulates a Transimpedance Amplifier
class TIAmplifier : public Block {

	bool firsTime{ true };

public:

	double gain = 1e6;
	double electricalNoiseSpectralDensity = 1e-4;

	default_random_engine generator;
	

	TIAmplifier() {};
	TIAmplifier(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};
	
	void initialize(void);
	bool runBlock(void);

	void setGain(double Gain) { gain = Gain; }
	double const getGain(void) { return gain; }

	void setNoiseSpectralDensity(double eNoiseSpectralDensity) { electricalNoiseSpectralDensity = eNoiseSpectralDensity; }
	double const getNoiseSpectralDensity(void) { return electricalNoiseSpectralDensity; }

private:
};


#endif // !PROGRAM_INCLUDE_TIAMPLIFIER_H_
