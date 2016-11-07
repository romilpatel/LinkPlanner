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

	int NumberOfBits(10000);

	if (NumberOfBits >= 512)
	{
		NumberOfBits = NumberOfBits + 512 + 8;
	}
	else
	{
		NumberOfBits = NumberOfBits + 8;
	}

	int SamplesPerSymbol(16);

	t_real SignalOutputPower_dBm = -20;


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
	B1.setBitPeriod(1.0 / 50e9);
	B1.setPatternLength(5);
	B1.setNumberOfBits(NumberOfBits);
	B1.setIqAmplitudes({ { 1, 0 }, { -1, 0 } });
	B1.setNumberOfSamplesPerSymbol(SamplesPerSymbol);
	B1.setRollOffFactor(0.3);
	B1.setSaveInternalSignals(false);

	testblock B2{ vector<Signal*> {&S00}, vector<Signal*> {&S01} };
	B2.setLocalOscillatorOpticalPower_dBm(-10);
	B2.setLocalOscillatorPhase(0.0);
	t_complex unit = 1;
	unit = 1 / sqrt(2) * unit;
	B2.setTransferMatrix({ { unit, unit, unit, -unit } });
	B2.setResponsivity(1);
	B2.setAmplification(1e6);
	B2.setNoiseAmplitude(1e-16);
	B2.setSamplingRate(SamplesPerSymbol);
	B2.setDelay(9);
	B2.setReferenceValue(0);

	BitErrorRate B3{ vector<Signal*> { &S01, &MQAM0 }, vector<Signal*> { &S02 } };
	B3.setConfidence(0.95);
	B3.setMidReportSize(0);

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