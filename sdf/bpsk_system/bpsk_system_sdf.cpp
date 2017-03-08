# include "netxpto.h"

# include "m_qam_transmitter.h"
# include "i_homodyne_receiver.h"
# include "sink.h"
# include "discrete_optical_amplifier.h"
# include "bit_error_rate.h"
# include "local_oscillator.h"
# include "balanced_beam_splitter.h"
# include "photodiode.h"
# include "ti_amplifier.h"

int main(){

	// #####################################################################################################
	// #################################### System Input Parameters ########################################
	// #####################################################################################################

	int numberOfBitsReceived(-1);
	int numberOfBitsGenerated(100);
	int samplesPerSymbol(100);
	int pLength = 5;
	double bitPeriod = 1.0 / 100e3;
	double rollOffFactor = 0.3;
	vector<t_iqValues> iqAmplitudeValues = { { -1, 0 }, { 1, 0 } };
	double signalOutputPower_dBm = -4; // doesn't matter right now
	double localOscillatorPower_dBm1 = -15;
	double localOscillatorPower2 = 0;
	double localOscillatorPhase1 = 0;
	double localOscillatorPhase2 = 0;
	array<t_complex, 4> transferMatrix = { { 1 / sqrt(2), 1 / sqrt(2), 1 / sqrt(2), -1 / sqrt(2)} };
	double responsivity = 1;
	double amplification = 1e6;
	double electricalNoiseAmplitude = 0.0022;
	int samplesToSkip = 16*16;// 8 * samplesPerSymbol;
	int bufferLength = 512;
	bool shotNoise(true);
		
	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	OpticalSignal S1("S1.sgn");
	S1.setBufferLength(bufferLength);

	OpticalSignal S2("S2.sgn");
	S2.setBufferLength(bufferLength);

	OpticalSignal S3("S3.sgn");
	S3.setBufferLength(bufferLength);

	OpticalSignal S4("S4.sgn");
	S4.setBufferLength(bufferLength);

	TimeContinuousAmplitudeContinuousReal S5("S5.sgn");
	S5.setBufferLength(bufferLength);

	TimeContinuousAmplitudeContinuousReal S6("S6.sgn");
	S6.setBufferLength(bufferLength);


	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################

	LocalOscillator B1{ vector<Signal*> { }, vector<Signal*> { &S1 } };
	B1.setOpticalPower_dBm(localOscillatorPower_dBm1);
	B1.setPhase(localOscillatorPhase1);
	B1.setSamplingPeriod(bitPeriod / samplesPerSymbol);
	B1.setSymbolPeriod(bitPeriod);

	LocalOscillator B2{ vector<Signal*> { }, vector<Signal*> { &S2 } };
	B2.setOpticalPower(localOscillatorPower2);
	B2.setPhase(localOscillatorPhase2);
	B2.setSamplingPeriod(bitPeriod / samplesPerSymbol);
	B2.setSymbolPeriod(bitPeriod);

	BalancedBeamSplitter B3{ vector<Signal*> {&S1, &S2}, vector<Signal*> {&S3, &S4} };
	B3.setTransferMatrix(transferMatrix);

	I_HomodyneReceiver B4{ vector<Signal*> {&S3, &S4}, vector<Signal*> {&S5} };
	B4.setResponsivity(responsivity);
	B4.setGain(amplification);
	B4.setElectricalNoiseSpectralDensity(electricalNoiseAmplitude);
	B4.setSaveInternalSignals(true);
	B4.useShotNoise(shotNoise);

	Sink B5{ vector<Signal*> { &S5 }, vector<Signal*> {} };
	B5.setNumberOfSamples(numberOfBitsReceived*samplesPerSymbol);
	B5.setDisplayNumberOfSamples(true);


	// #####################################################################################################
	// ########################### System Declaration and Inicialization ###################################
	// #####################################################################################################

	System MainSystem{ vector<Block*> { &B1, &B2, &B3, &B4, &B5 } };

	// #####################################################################################################
	// #################################### System Run #####################################################
	// #####################################################################################################

	MainSystem.run();

	return 0;

}