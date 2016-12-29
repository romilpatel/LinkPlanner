# ifndef PROGRAM_INCLUDE_WHITE_NOISE_H_
# define PROGRAM_INCLUDE_WHITE_NOISE_H_

# include "netxpto.h"
# include <vector>
#include <random>

// Simulates a Transimpedance Amplifier
class WhiteNoise : public Block {

	bool firsTime{ true };

public:

	t_real noisebias = 0;
	t_real noiseamp = 1e-4;
	int noiseLength = 0;
	double samplingPeriod{ 0.0 };
	double symbolPeriod{ 0.0 };

	default_random_engine generator1;
	default_random_engine generator2;


	WhiteNoise() {};
	WhiteNoise(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};
	
	void initialize(void);
	bool runBlock(void);

	void setSamplingPeriod(double sPeriod) { samplingPeriod = sPeriod; }
	void setSymbolPeriod(double sPeriod) { symbolPeriod = sPeriod; }
	void setNoiseAmplitude(t_real NoiseAmplitude) { noiseamp = NoiseAmplitude; }
	void setNoiseBias(t_real nBias) { noisebias = nBias; };
	void setNoiseLength(int nLength) { noiseLength = noiseLength; };

private:
};


#endif // !PROGRAM_INCLUDE_TIAMPLIFIER_H_
