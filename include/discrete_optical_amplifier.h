# ifndef PROGRAM_DISCRETE_OPTICAL_AMPLIFIER_H_
# define PROGRAM_DISCRETE_OPTICAL_AMPLIFIER_H_

# include "netxpto.h"

# include "ideal_amplifier.h"
# include "add.h"
# include "white_noise.h"


// Implements a Discrete Optical Amplifier
class DiscreteOpticalAmplifier : public SuperBlock {

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
<<<<<<< HEAD:include/edfa.h
	double gain{ 1e4 };
=======
	double amplification{ 1e4 };

	t_real std{ 1e-3 };
	t_real noiseBias{ 0 };
>>>>>>> 14adca355faa92683b01e2a95152ddb168447487:include/discrete_optical_amplifier.h

	double bilateralNoiseSpectralDensity{ 1e-3 }; // W/Hz
	

public:

	/* Methods */

	DiscreteOpticalAmplifier(vector<Signal *> &inputSignal, vector<Signal *> &outputSignal);

	/* Set Methods */

<<<<<<< HEAD:include/edfa.h
	void setDiscreteOpticalAmplifierGain(double gain) { B1.setGain(gain); };
	double getDiscreteOpticalAmplifierGain() { return B1.getGain(); };

	void setDiscreteOpticalAmplifierBilateralNoiseSpectralDensity(double bNoiseSpectralDensity) { B2.setBilateralNoiseSpectralDensity(bNoiseSpectralDensity); };
=======
	void setGain(double gain) { B1.setGain(gain); };

	void setOpticalNoiseSpectralDensity(double std) { B2.setNoiseSpectralDensity(std); };
	double const getOpticalNoiseSpectralDensity(void) { B2.getNoiseSpectralDensity(); }
>>>>>>> 14adca355faa92683b01e2a95152ddb168447487:include/discrete_optical_amplifier.h

};

#endif
