# include "netxpto.h"

# include "m_qam_transmitter.h"
# include "i_homodyne_receiver.h"
# include "sink.h"
# include "discrete_optical_amplifier.h"
# include "bit_error_rate.h"

int main(){

	// #####################################################################################################
	// #################################### System Input Parameters ########################################
	// #####################################################################################################

	int numberOfBitsReceived(-1);
	int numberOfBitsGenerated(20);
	int samplesPerSymbol(16);
	int pLength = 5;
	double bitPeriod = 1.0 / 50e9;
	double rollOffFactor = 0.3;
	vector<t_iqValues> iqAmplitudeValues = { { -1, 0 }, { 1, 0 } };
	double signalOutputPower_dBm = -20;
	double localOscillatorPower_dBm = -10;
	double localOscillatorPhase = 0;
	array<t_complex, 4> transferMatrix = { { 1 / sqrt(2), 1 / sqrt(2), 1 / sqrt(2), -1 / sqrt(2)} };
	double responsivity = 1;
	double amplification = 10e6;
	double electricalNoiseAmplitude = 1e-3;
	double opticalNoiseAmplitude = 1e-3;
	int samplesToSkip = 8 * samplesPerSymbol;
	int bufferLength = 512;
	bool shotNoise(false);
		
	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	Binary S0{ "S0.sgn" };
	S0.setBufferLength(bufferLength);

	OpticalSignal S1("S1.sgn");
	S1.setBufferLength(bufferLength);

	OpticalSignal S2("S2.sgn");
	S2.setBufferLength(bufferLength);

	Binary S3{ "S3.sgn" };
	S3.setBufferLength(bufferLength);

	Binary S4{ "S4.sgn" };
	S4.setBufferLength(bufferLength);

	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################

	MQamTransmitter B1{ vector<Signal*> { }, vector<Signal*> { &S1, &S0 } };
	B1.setNumberOfBits(numberOfBitsGenerated);
	B1.setOutputOpticalPower_dBm(signalOutputPower_dBm);
	B1.setMode(DeterministicAppendZeros);
	B1.setBitStream("010");
	B1.setBitPeriod(bitPeriod);
	B1.setPatternLength(pLength);
	B1.setIqAmplitudes(iqAmplitudeValues);
	B1.setNumberOfSamplesPerSymbol(samplesPerSymbol);
	B1.setRollOffFactor(rollOffFactor);
	B1.setSaveInternalSignals(false);
	B1.setSeeBeginningOfImpulseResponse(true);

	DiscreteOpticalAmplifier B2{ vector<Signal*> {&S1}, vector<Signal*> {&S2} };
	B2.setOpticalNoiseSpectralDensity(opticalNoiseAmplitude);
	B2.setGain(1e3);
	
	I_HomodyneReceiver B3{ vector<Signal*> {&S2}, vector<Signal*> {&S3} };
	B3.setLocalOscillatorOpticalPower_dBm(localOscillatorPower_dBm);
	B3.setLocalOscillatorPhase(localOscillatorPhase);
	B3.setLocalOscillatorSamplingPeriod(bitPeriod / samplesPerSymbol);
	B3.setLocalOscillatorSymbolPeriod(bitPeriod);
	B3.setTransferMatrix(transferMatrix);
	B3.setResponsivity(responsivity);
	B3.setGain(amplification);
	B3.setElectricalNoiseSpectralDensity(electricalNoiseAmplitude);
	B3.setSamplesToSkip(samplesToSkip);
	B3.setSaveInternalSignals(false);
	B3.useShotNoise(shotNoise);

	BitErrorRate B4{ vector<Signal*> { &S0, &S3 }, vector<Signal*> { &S4 } };
	B4.setConfidence(.95);

	Sink B5{ vector<Signal*> { &S4 }, vector<Signal*> {} };
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