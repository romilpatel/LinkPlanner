# ifndef PROGRAM_INCLUDE_I_HOMODYNE_RECEIVER_H_
# define PROGRAM_INCLUDE_I_HOMODYNE_RECEIVER_H_

# include "netxpto.h"

# include "local_oscillator.h"
# include "balanced_beam_splitter.h"
# include "photodiode.h"
# include "ti_amplifier.h"
# include "electrical_filter.h"
# include "sampler.h"
# include "bit_decider.h"


// Balanced Homodyne Receiver superblock
class I_HomodyneReceiver : public SuperBlock {

	// #####################################################################################################
	// ################## Internal Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	OpticalSignal I_HMD01{ "I_HMD01.sgn" }; // Local Oscillator

	OpticalSignal I_HMD02{ "I_HMD02.sgn" }; // BS Out 1 -> S + LO

	OpticalSignal I_HMD03{ "I_HMD03.sgn" }; // BS Out 2 -> S - LO

	TimeContinuousAmplitudeContinuousReal I_HMD04{ "I_HMD04.sgn" }; // Detected and Subtracted -> 4*S*LO

	TimeContinuousAmplitudeContinuousReal I_HMD05{ "I_HMD05.sgn" }; // Amplified

	TimeContinuousAmplitudeContinuousReal I_HMD06{ "I_HMD06.sgn" }; // Filtered

	TimeDiscreteAmplitudeContinuousReal I_HMD07{ "I_HMD07.sgn" }; // Sampled

	Binary I_HMD08{ "I_HMD08.sgn" }; // Binary retrieved information


	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################

	LocalOscillator B1;

	BalancedBeamSplitter B2;

	Photodiode B3;

	TIAmplifier B4;

	ElectricalFilter B5;

	Sampler B6;

	BitDecider B7;

	/* State Variables */

	/* Input Parameters */
	double samplingPeriod{ 0.0 };

	double localOscillatorOpticalPower{ 1e-3 };
	double localOscillatorPhase{ 0 };
	double localOscillatorWavelength{ 1550e-9 };

	int samplesToSkip{ 0 };

	double outputOpticalFrequency{ SPEED_OF_LIGHT / localOscillatorWavelength };

public:

	/* Methods */

	I_HomodyneReceiver(vector<Signal *> &inputSignal, vector<Signal *> &outputSignal);

	/* Set Methods */

	void setLocalOscillatorSamplingPeriod(double sPeriod) { B1.setSamplingPeriod(sPeriod); };
	void setLocalOscillatorSymbolPeriod(double sPeriod) { B1.setSymbolPeriod(sPeriod); }
	void setLocalOscillatorOpticalPower(double opticalPower) { B1.setOpticalPower(opticalPower); };
	void setLocalOscillatorOpticalPower_dBm(double opticalPower_dBm) { B1.setOpticalPower_dBm(opticalPower_dBm); };
	void setLocalOscillatorPhase(double lOscillatorPhase) { B1.setPhase(lOscillatorPhase); };
	double const getLocalOscillatorPhase(void) { B1.getPhase(); }
	void setLocalOscillatorOpticalWavelength(double lOscillatorWavelength) { B1.setWavelength(lOscillatorWavelength); };

	void setSamplingPeriod(double sPeriod) { B1.setSamplingPeriod(sPeriod); };

	void setTransferMatrix(array<t_complex, 4> TransferMatrix) { B2.matrix = TransferMatrix; };
	array<complex<double>, 4> const getBalancedBeamsplitter(void) { B2.getTransferMatrix(); }

	void setResponsivity(double Responsivity) { B3.setResponsivity(Responsivity); };
	double const getResponsivity(void) { B3.getResponsivity(); }
	void useShotNoise(bool uShotNoise){ B3.useNoise(uShotNoise); };

	void setGain(double Gain) { B4.setGain(Gain); }

	void setElectricalNoiseSpectralDensity(double eNoiseSpectralDensity) { B4.setNoiseSpectralDensity(eNoiseSpectralDensity); }
	double const getElectricalNoiseSpectralDensity(void) { B4.getNoiseSpectralDensity(); }

	void setSamplesToSkip(int sToSkip) { B6.setSamplesToSkip(sToSkip); };
	int const getSamplesToSkip(void) { B6.getSamplesToSkip(); }

	void setDecionLevel(int dLevel) { B7.setDecisionLevel(dLevel); };
	double const getDecisionLevel(void) { B7.getDecisionLevel(); }

};

#endif
