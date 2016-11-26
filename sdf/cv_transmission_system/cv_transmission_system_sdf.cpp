# include "netxpto.h"

# include "sink.h"
# include "balanced_beam_splitter.h"
# include "subtractor.h"
# include "photodiode.h"
# include "ti_amplifier.h"
# include "local_oscillator.h"
# include "sampler.h"
# include "bit_decider.h"
# include "bit_error_rate.h"
# include "testblock.h"
# include "m_qam_transmitter.h"
# include "binary_source.h"
# include "electrical_filter.h"

#define _USE_MATH_DEFINES // for C
#include <math.h>

int main(){

	// #####################################################################################################
	// #################################### System Input Parameters ########################################
	// #####################################################################################################

	int NumberOfBits(1000);
	int SamplesPerSymbol(16);
	t_real SignalOutputPower_dBm = -20;


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

	OpticalSignal S01("S01.sgn");

	OpticalSignal S02("S02.sgn");

	OpticalSignal S03("S03.sgn");

	OpticalSignal S04("S04.sgn");

	TimeContinuousAmplitudeContinuousReal S05{ "S05.sgn" };

	TimeContinuousAmplitudeContinuousReal S06{ "S06.sgn" };

	TimeContinuousAmplitudeContinuousReal S07{ "S07.sgn" };

	TimeDiscreteAmplitudeContinuousReal S08{ "S08.sgn" };

	Binary S09{ "S09.sgn" };

	Binary S10{ "S10.sgn" };


	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################

	MQamTransmitter B1{ vector<Signal*> { }, vector<Signal*> { &S00, &MQAM0 } };
	B1.setOutputOpticalPower_dBm(-40);
	B1.setMode(PseudoRandom);
	B1.setBitPeriod(1.0 / 50e9);
	B1.setPatternLength(5);
	B1.setNumberOfBits(NumberOfBits);
	B1.setIqAmplitudes({ { 1, 0 }, { -1, 0 } });
	B1.setNumberOfSamplesPerSymbol(SamplesPerSymbol);
	B1.setRollOffFactor(0.3);
	B1.setSaveInternalSignals(false);

	LocalOscillator B2{ vector<Signal*> { &S00 }, vector<Signal*> { &S01, &S02 } };
	B2.setLocalOscillatorOpticalPower_dBm(-20);
	B2.setLocalOscillatorPhase(PI);

	BalancedBeamSplitter B3{ vector<Signal*> { &S01, &S02 }, vector<Signal*> { &S03, &S04 } };
	t_complex unit = 1;
	unit = 1 / sqrt(2) * unit;
	B3.setTransferMatrix({ { unit, unit, unit, -unit } });

	Photodiode B4{ vector<Signal*> { &S03, &S04 }, vector<Signal*> { &S05 } };
	B4.setResponsivity(1);

	TIAmplifier B5{ vector<Signal*> { &S05 }, vector<Signal*> { &S06 } };
	B5.setAmplification(1e6);
	B5.setNoiseAmplitude(3.1937e-5); //noise levels for project's result

	ElectricalFilter B6{ vector<Signal*> { &S06 }, vector<Signal*> { &S07 } };

	Sampler B7{ vector<Signal*> { &S07 }, vector<Signal*> { &S08 } };
	B7.setSamplingRate(SamplesPerSymbol);
	B7.setDelay(17);

	BitDecider B8{ vector<Signal*> { &S08 }, vector<Signal*> { &S09 } };
	
	BitErrorRate B9{ vector<Signal*> { &S09, &MQAM0 }, vector<Signal*> { &S10 } };
	B9.setConfidence(0.95);
	B9.setMidReportSize(0);

	Sink B10{ vector<Signal*> { &S10 }, vector<Signal*> {} };
	B10.setNumberOfSamples(50000);
	B10.setDisplayNumberOfSamples(false);

	// #####################################################################################################
	// ########################### System Declaration and Inicialization ###################################
	// #####################################################################################################

	System MainSystem{ vector<Block*> { &B1, &B2, &B3, &B4, &B5, &B6, &B7, &B8, &B9, &B10 } };

	// #####################################################################################################
	// #################################### System Run #####################################################
	// #####################################################################################################
	
	MainSystem.run();

	return 0;

}