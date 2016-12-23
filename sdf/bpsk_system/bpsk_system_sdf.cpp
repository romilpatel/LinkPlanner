# include "netxpto.h"

# include "m_qam_transmitter.h"
# include "i_homodyne_receiver.h"
# include "bit_error_rate.h"
# include "sink.h"

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
	double noiseAmplitude = 1e-16;
	int samplesToSkip = 8 * samplesPerSymbol + floor(samplesPerSymbol/2);
	double confidence = 0.95;
	int midReportSize = 0;
	int bufferLength = 256;
		
	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	Binary S0{ "S0.sgn" };
	S0.setBufferLength(bufferLength);

	OpticalSignal S1("S1.sgn");
	S1.setBufferLength(bufferLength);

	Binary S2{ "S2.sgn" };
	S2.setBufferLength(bufferLength);

	Binary S3{ "S3.sgn" };
	S3.setBufferLength(bufferLength);

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
	B1.setSaveInternalSignals(true);
	B1.setSeeBeginningOfImpulseResponse(true);

	I_HomodyneReceiver B2{ vector<Signal*> {&S1}, vector<Signal*> {&S2} };
	B2.setLocalOscillatorOpticalPower_dBm(localOscillatorPower_dBm);
	B2.setLocalOscillatorPhase(localOscillatorPhase);
	B2.setTransferMatrix(transferMatrix);
	B2.setResponsivity(responsivity);
	B2.setAmplification(amplification);
	B2.setNoiseAmplitude(noiseAmplitude);
	B2.setSamplesToSkip(samplesToSkip);
	B2.setPosReferenceValue(0);
	B2.setNegReferenceValue(0);
	B2.setSaveInternalSignals(true);

	BitErrorRate B3{ vector<Signal*> { &S2, &S0 }, vector<Signal*> { &S3 } };
	B3.setConfidence(confidence);
	B3.setMidReportSize(midReportSize);

	Sink B4{ vector<Signal*> { &S3 }, vector<Signal*> {} };
	B4.setNumberOfSamples(numberOfBitsReceived*samplesPerSymbol);
	B4.setDisplayNumberOfSamples(true);


	// #####################################################################################################
	// ########################### System Declaration and Inicialization ###################################
	// #####################################################################################################

	System MainSystem{ vector<Block*> { &B1, &B2, &B3, &B4 } };

	// #####################################################################################################
	// #################################### System Run #####################################################
	// #####################################################################################################
	
	MainSystem.run();

	return 0;

}