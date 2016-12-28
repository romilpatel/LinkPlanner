# ifndef PROGRAM_EDFA_H_
# define PROGRAM_EDFA_H_

# include "netxpto.h"

# include "ideal_amplifier.h"
# include "add.h"
# include "white_noise.h"


// this is a test block for the purpose of beta testing new code
// current code: Building Homodyne superblock.
class EDFA : public SuperBlock {

	// #####################################################################################################
	// ################## Internal Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	OpticalSignal EDFA01{ "EDFA01.sgn" }; // Amplified

	OpticalSignal EDFA02{ "EDFA02.sgn" }; // White Noise

	OpticalSignal EDFA03{ "EDFA03.sgn" }; // Out Signal

	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################

	IdealAmplifier B1;

	WhiteNoise B2;

	Add B3;

	/* State Variables */

	/* Input Parameters */
	double amplification{ 1e4 };

	t_real std{ 1e-3 };
	t_real noiseBias{ 0 };
	int noiseLength{ 512 };


public:

	/* Methods */

	EDFA(vector<Signal *> &inputSignal, vector<Signal *> &outputSignal);

	/* Set Methods */

	void setAmplification(double amp) { B1.setAmplification(amp); };

	void setOpticalNoiseAmplitude(double std) { B2.setNoiseAmplitude(std); };
	void setNoiseBias(double nBias) { B2.setNoiseBias(nBias); };
	void setNoiseSamplingPeriod(double sPeriod) { B2.setSamplingPeriod(sPeriod); };
	void setNoiseSymbolPeriod(double sPeriod){ B2.setSymbolPeriod(sPeriod); };

	void useOpticalNoise(bool oNoise){ B3.useNoise(oNoise); }

};

#endif
