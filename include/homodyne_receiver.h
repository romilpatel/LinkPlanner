# ifndef PROGRAM_INCLUDE_HOMODYNE_RECEIVER_H_
# define PROGRAM_INCLUDE_HOMODYNE_RECEIVER_H_

# include "netxpto.h"
# include "balanced_beam_splitter.h"
# include "photodiode.h"
# include "subtractor.h"
# include "ti_amplifier.h"
# include "bit_decider.h"
# include "local_oscillator.h"
# include "sampler.h"
# include "delayer.h"
# include "super_block_interface.h"


// this is a test block for the purpose of beta testing new code
// current code: Building Homodyne superblock.
class HomodyneReceiver : public SuperBlock {

	/* State Variables */

	// #####################################################################################################
	// ################## Internal Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	OpticalSignal HMD00{ "HMD00.sgn" }; // Signal after local_oscillator block

	OpticalSignal HMD01{ "HMD01.sgn" }; // Local Oscillator

	OpticalSignal HMD02{ "HMD02.sgn" }; // BS Out 1

	OpticalSignal HMD03{ "HMD03.sgn" }; // BS Out 2

	TimeContinuousAmplitudeContinuousReal HMD04{ "HMD04.sgn" }; // Detected and Subtracted

	TimeContinuousAmplitudeContinuousReal HMD05{ "HMD05.sgn" }; // Amplified

	TimeDiscreteAmplitudeContinuousReal HMD06{ "HMD06.sgn" }; // Sampled and Delayed

	Binary HMD07{ "HMD07.sgn" }; // Evaluated

	Binary HMD08{ "HMD08.sgn" }; // Output, not sure if needed

	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################

	LocalOscillator B1;

	BalancedBeamSplitter B2;

	Photodiode B3;

	TIAmplifier B4;

	Sampler B5;

	BitDecider B6;

	SuperBlockInterface B7;

	/* Input Parameters */


public:

	/* Methods */

	HomodyneReceiver(vector<Signal *> &inputSignal, vector<Signal *> &outputSignal);

	/* Set Methods */

	void setLocalOscillatorOpticalPower(double outOpticalPower) { B1.outputOpticalPower=outOpticalPower; };
	void setLocalOscillatorOpticalPower_dBm(double outOpticalPower_dBm) { B1.outputOpticalPower = 1e-3*pow(10, outOpticalPower_dBm / 10); };
	void setLocalOscillatorPhase(double LOPhase) { B1.LocalOscillatorPhase = LOPhase; };

	void setTransferMatrix(array<t_complex, 4> TransferMatrix) { B2.matrix = TransferMatrix; };

	void  setResponsivity(t_real Responsivity) { B3.responsivity = Responsivity; };

	void setAmplification(t_real Amplification) { B4.amplification = Amplification; };
	void setNoiseAmplitude(t_real NoiseAmplitude) { B4.noiseamp = NoiseAmplitude; };

	void setSamplingRate(int Sampling) { B5.sampling = Sampling; };
	void setDelay(int Delay) { B5.delay = Delay; };

	void setPosReferenceValue(int ReferenceValue) { B6.posreferencevalue = ReferenceValue; };
	void setNegReferenceValue(int ReferenceValue) { B6.negreferencevalue = ReferenceValue; };
};

#endif
