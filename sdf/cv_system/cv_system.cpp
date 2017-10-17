# include "netxpto.h"

# include "m_qam_transmitter.h"
# include "i_homodyne_receiver.h"
# include "bit_error_rate.h"
# include "local_oscillator.h"
# include "balanced_beam_splitter.h"
# include "photodiode.h"
# include "ti_amplifier.h"
# include "sampler.h"
# include "sink.h"
# include "optical_hybrid.h"

int main() {

	// #####################################################################################################
	// #################################### System Input Parameters ########################################
	// #####################################################################################################

	int numberOfBitsReceived(-1);
	int numberOfBitsGenerated(20);
	int samplesPerSymbol(16);
	int pLength = 5;
	double bitPeriod = 1.0e-9;
	double rollOffFactor = 0.3;
	vector<t_iqValues> iqAmplitudeValues = { { 1, 1 },{ -1, 1 },{ -1, -1 },{ 1, -1 } }; //{ { -1, -1 },{ 1, 1 } };//
	//double signalOutputPower = 1.025651926251408e-09; // doesn't matter right now
	double signalOutputPower = 1;
	double localOscillatorPower_dBm1 = 7;
	double localOscillatorPhase = 0;
	array<t_complex, 4> transferMatrix = { { 1 / sqrt(2), 1 / sqrt(2), 1 / sqrt(2), -1 / sqrt(2) } };
	double responsivity = 1;
	double amplification = 1e2;
	double electricalNoiseAmplitude = 0.0341;
	int samplesToSkip = 8 * samplesPerSymbol;
	int bufferLength = 512;
	bool shotNoise(true);

	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	Binary S0("S0.sgn");
	S0.setBufferLength(bufferLength);

	OpticalSignal S1("S1.sgn");
	S1.setBufferLength(bufferLength);

	OpticalSignal S2("S2.sgn");
	S2.setBufferLength(bufferLength);

	OpticalSignal S3("S3.sgn");
	S3.setBufferLength(bufferLength);

	OpticalSignal S4("S4.sgn");
	S4.setBufferLength(bufferLength);

	OpticalSignal S5("S5.sgn");
	S5.setBufferLength(bufferLength);

	OpticalSignal S6("S6.sgn");
	S6.setBufferLength(bufferLength);

	TimeContinuousAmplitudeContinuousReal S71("S71.sgn");
	S71.setBufferLength(bufferLength);

	TimeContinuousAmplitudeContinuousReal S81("S81.sgn");
	S81.setBufferLength(bufferLength);

	TimeDiscreteAmplitudeContinuousReal S91("S91.sgn");
	S91.setBufferLength(bufferLength);

	TimeContinuousAmplitudeContinuousReal S72("S72.sgn");
	S72.setBufferLength(bufferLength);

	TimeContinuousAmplitudeContinuousReal S82("S82.sgn");
	S82.setBufferLength(bufferLength);

	TimeDiscreteAmplitudeContinuousReal S92("S92.sgn");
	S92.setBufferLength(bufferLength);

	Binary S10("S10.sgn");
	S10.setBufferLength(bufferLength);

	Binary S11("S11.sgn");
	S11.setBufferLength(bufferLength);

	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################

	MQamTransmitter B1{ vector<Signal*> {}, vector<Signal*> {&S1, &S0} };
	B1.setNumberOfBits(numberOfBitsGenerated);
	B1.setOutputOpticalPower(signalOutputPower);
	B1.setMode(PseudoRandom);
	B1.setBitPeriod(bitPeriod);
	B1.setPatternLength(pLength);
	B1.setIqAmplitudes(iqAmplitudeValues);
	B1.setNumberOfSamplesPerSymbol(samplesPerSymbol);
	B1.setRollOffFactor(rollOffFactor);
	B1.setSaveInternalSignals(true);
	B1.setPulseShaperFilter(Gaussian);
	B1.setSeeBeginningOfImpulseResponse(true);

	LocalOscillator B2{ vector<Signal*> { }, vector<Signal*> { &S2 } };
	B2.setOpticalPower(localOscillatorPower_dBm1);
	B2.setPhase(localOscillatorPhase);
	B2.setSamplingPeriod(bitPeriod / samplesPerSymbol);
	B2.setSymbolPeriod(bitPeriod);

	OpticalHybrid B3{ vector<Signal*> {&S1, &S2}, vector<Signal*> {&S3, &S4, &S5, &S6} };

	Photodiode B41{ vector<Signal*> {&S3, &S4}, vector<Signal*> {&S71} };
	B41.useNoise(shotNoise);
	B41.setResponsivity(responsivity);

	TI_Amplifier B51{ vector<Signal*> {&S71}, vector<Signal*> {&S81} };
	B51.setGain(amplification);
	B51.setElectricalNoiseSpectralDensity(electricalNoiseAmplitude);
	B51.setSaveInternalSignals(true);
	B51.setSeeBeginningOfImpulseResponse(false);
	B51.setImpulseResponseLength(16);
	B51.setRollOffFactor(0);
	B51.usePassiveFilterMode(true);

	Sampler B61{ vector<Signal*> {&S81}, vector<Signal*> {&S91} };
	B61.setSamplesToSkip(samplesToSkip);

	Photodiode B42{ vector<Signal*> {&S5, &S6}, vector<Signal*> {&S72} };
	B42.useNoise(shotNoise);
	B42.setResponsivity(responsivity);

	TI_Amplifier B52{ vector<Signal*> {&S72}, vector<Signal*> {&S82} };
	B52.setGain(amplification);
	B52.setElectricalNoiseSpectralDensity(electricalNoiseAmplitude);
	B52.setSaveInternalSignals(true);
	B52.setSeeBeginningOfImpulseResponse(false);
	B52.setImpulseResponseLength(16);
	B52.setRollOffFactor(0);
	B52.usePassiveFilterMode(true);

	Sampler B62{ vector<Signal*> {&S82}, vector<Signal*> {&S92} };
	B62.setSamplesToSkip(samplesToSkip);

	BitDecider B7{ vector<Signal*> {&S91, &S92}, vector<Signal*> {&S10} };

	BitErrorRate B8{ vector<Signal*> {&S0, &S10}, vector<Signal*> {&S11} };
	// First the original, then the recovered one
	B8.setSizeConstellation(4);

	Sink B9{ vector<Signal*> { &S11 }, vector<Signal*> {} };
	B9.setNumberOfSamples(samplesPerSymbol*numberOfBitsGenerated);
	B9.setDisplayNumberOfSamples(true);


	// #####################################################################################################
	// ########################### System Declaration and Inicialization ###################################
	// #####################################################################################################

	System MainSystem{ vector<Block*> { &B1, &B2, &B3, &B41, &B51, &B61, &B42, &B52, &B62, &B7, &B8, &B9 } };

	// #####################################################################################################
	// #################################### System Run #####################################################
	// #####################################################################################################

	MainSystem.run();

	return 0;

}
