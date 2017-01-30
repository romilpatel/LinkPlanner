# ifndef PROGRAM_INCLUDE_I_HOMODYNE_RECEIVER_H_
# define PROGRAM_INCLUDE_I_HOMODYNE_RECEIVER_H_

# include "netxpto.h"

# include "local_oscillator.h"
# include "balanced_beam_splitter.h"
# include "photodiode.h"
# include "ti_amplifier.h"
# include "sampler.h"
# include "bit_decider.h"


// this is a test block for the purpose of beta testing new code
// current code: Building Homodyne superblock.
class I_HomodyneReceiver : public SuperBlock {

	// #####################################################################################################
	// ################## Internal Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	OpticalSignal I_HMD01{ "I_HMD01.sgn" }; // Local Oscillator

	OpticalSignal I_HMD02{ "I_HMD02.sgn" }; // BS Out 1 -> S + LO

	OpticalSignal I_HMD03{ "I_HMD03.sgn" }; // BS Out 2 -> S - LO

	TimeContinuousAmplitudeContinuousReal I_HMD04{ "I_HMD04.sgn" }; // Detected and Subtracted -> 4*S*LO

	TimeContinuousAmplitudeContinuousReal I_HMD05{ "I_HMD05.sgn" }; // Amplified

	TimeDiscreteAmplitudeContinuousReal I_HMD06{ "I_HMD06.sgn" }; // Sampled

	Binary I_HMD07{ "I_HMD07.sgn" }; // Binary retrieved information


	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################

	LocalOscillator B1;

	BalancedBeamSplitter B2;

	Photodiode B3;

	TIAmplifier B4;

	Sampler B5;

	BitDecider B6;

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
	//void setLocalOscillatorSymbolPeriod(double sPeriod) { B1.setSymbolPeriod(sPeriod); }
	void setLocalOscillatorOpticalPower(double opticalPower) { B1.setOpticalPower(opticalPower); };
	void setLocalOscillatorOpticalPower_dBm(double opticalPower_dBm) { B1.setOpticalPower_dBm(opticalPower_dBm); };
	void setLocalOscillatorPhase(double lOscillatorPhase) { B1.setPhase(lOscillatorPhase); };
	void setLocalOscillatorOpticalWavelength(double lOscillatorWavelength) { B1.setWavelength(lOscillatorWavelength); };

	void setSamplingPeriod(double sPeriod) { B1.setSamplingPeriod(sPeriod); };

	void setTransferMatrix(array<t_complex, 4> TransferMatrix) { B2.matrix = TransferMatrix; };

	void  setResponsivity(t_real Responsivity) { B3.responsivity = Responsivity; };

	void setAmplification(t_real Amplification) { B4.amplification = Amplification; };
	void setNoiseAmplitude(t_real NoiseAmplitude) { B4.noiseamp = NoiseAmplitude; };

	void setSamplesToSkip(int sToSkip) { B5.setSamplesToSkip(sToSkip); };

	void setDecionLevel(int dLevel) { B6.setDecisionLevel(dLevel); };

};

#endif
