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
	double gain{ 1e4 };

	double bilateralNoiseSpectralDensity{ 1e-3 }; // W/Hz
	

public:

	/* Methods */

	EDFA(vector<Signal *> &inputSignal, vector<Signal *> &outputSignal);

	/* Set Methods */

	void setDiscreteOpticalAmplifierGain(double gain) { B1.setGain(gain); };
	double getDiscreteOpticalAmplifierGain() { return B1.getGain(); };

	void setDiscreteOpticalAmplifierBilateralNoiseSpectralDensity(double bNoiseSpectralDensity) { B2.setBilateralNoiseSpectralDensity(bNoiseSpectralDensity); };

};

#endif
