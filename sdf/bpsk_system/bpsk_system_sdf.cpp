# include "netxpto.h"

# include "sink.h"
# include "balanced_beam_splitter.h"
# include "subtractor.h"
# include "photodiode.h"
# include "ti_amplifier.h"
# include "local_oscillator.h"
# include "discretizer.h"
# include "delayer.h"
# include "bit_decider.h"
# include "bit_error_rate.h"
# include "testblock.h"
# include "discarder.h"
# include "m_qam_transmitter.h"
# include "binary_source.h"


#define _USE_MATH_DEFINES // for C
#include <math.h>

int main(){

	// #####################################################################################################
	// #################################### System Input Parameters ########################################
	// #####################################################################################################

	int NumberOfBits(9000);
	int SamplesPerSymbol(16);
	int pLength = 5;
	t_real bitPeriod = 1.0 / 50e9;
	vector<t_iqValues> iqAmplitudeValues = { { 1, 0 }, { -1, 0 } };
	t_real SignalOutputPower_dBm = -20;
	t_real LOoutOpticalPower_dBm = -10;
	t_real LocalOscillatorPhase = 0;
	array<t_complex, 4> TransferMatrix = { { 1 / sqrt(2), 1 / sqrt(2), 1 / sqrt(2), -1 / sqrt(2)} };
	t_real Responsivity = 1;
	t_real Amplification = 10e6;
	t_real NoiseAmplitude = 1e-16;
	int Delay = 9;
	t_real Confidence = 0.95;
	int midReportSize = 0;

	if (NumberOfBits >= 512)
	{
		NumberOfBits = NumberOfBits + 512 + 8;
	}
	else
	{
		NumberOfBits = NumberOfBits + 8;
	}

	
	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	Binary MQAM0{ "MQAM0.sgn" };

	OpticalSignal S00("S00.sgn");

	Binary S01{ "S01.sgn" };
	 
	Binary S02{ "S02.sgn" };


	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################

	MQamTransmitter B1{ vector<Signal*> { }, vector<Signal*> { &S00, &MQAM0 } };
	B1.setOutputOpticalPower_dBm(SignalOutputPower_dBm);
	B1.setMode(PseudoRandom);
	B1.setBitPeriod(bitPeriod);
	B1.setPatternLength(pLength);
	B1.setNumberOfBits(NumberOfBits);
	B1.setIqAmplitudes(iqAmplitudeValues);
	B1.setNumberOfSamplesPerSymbol(SamplesPerSymbol);
	B1.setRollOffFactor(0.3);
	B1.setSaveInternalSignals(false);

	testblock B2{ vector<Signal*> {&S00}, vector<Signal*> {&S01} };
	B2.setLocalOscillatorOpticalPower_dBm(LOoutOpticalPower_dBm);
	B2.setLocalOscillatorPhase(LocalOscillatorPhase);
	B2.setTransferMatrix(TransferMatrix);
	B2.setResponsivity(Responsivity);
	B2.setAmplification(Amplification);
	B2.setNoiseAmplitude(NoiseAmplitude);
	B2.setSamplingRate(SamplesPerSymbol);
	B2.setDelay(Delay);
	B2.setPosReferenceValue(0);
	B2.setNegReferenceValue(0);

	BitErrorRate B3{ vector<Signal*> { &S01, &MQAM0 }, vector<Signal*> { &S02 } };
	B3.setConfidence(Confidence);
	B3.setMidReportSize(midReportSize);

	Sink B4{ vector<Signal*> { &S02 }, vector<Signal*> {} };
	B4.setNumberOfSamples(50000);
	B4.setDisplayNumberOfSamples(false);

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