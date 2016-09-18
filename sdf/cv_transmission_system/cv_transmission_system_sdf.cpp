# include "m_qam_transmitter.h"
# include "sink.h"
# include "laser.h"
# include "BalancedBeamsplitter.h"
# include "subtractor.h"
# include "photodiodeplus.h"
# include "photodiodeminus.h"
# include "BPSKMODULATOR.h"
# include "bpsk_mapper.h"
# include "TIamplifier.h"
# include "local_oscillator.h"
# include "discrete_to_continuous_time.h"
# include "discretizer.h"
# include "delayer.h"
# include "bit_decider.h"
# include "bit_error_rate.h"
# include "testblock.h"
# include "discarder.h"

# include "binary_source.h"
# include "pulse_shaper.h"

#define _USE_MATH_DEFINES // for C
#include <math.h>

int main(){

	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################


	Binary MQAM1{ "MQAM1.sgn" };

	Binary MQAM0{ "MQAM0.sgn" };

	Binary MQAM00{ "MQAM00.sgn" };

	BandpassSignal S1("S1.sgn");

	BandpassSignal S2("S2.sgn");

	BandpassSignal S3{ "S3.sgn" };

	BandpassSignal S4{ "S4.sgn" };

	TimeContinuousAmplitudeContinuousReal S5{ "S5.sgn" };

	TimeContinuousAmplitudeContinuousReal S6{ "S6.sgn" };

	TimeContinuousAmplitudeContinuousReal S7{ "S7.sgn" };

	TimeContinuousAmplitudeContinuousReal S8{ "S8.sgn" };

	TimeDiscreteAmplitudeContinuousReal S9{ "S9.sgn" };
	
	TimeDiscreteAmplitudeContinuousReal S10{ "S10.sgn" };

	Binary S11{ "S11.sgn" };

	Binary S12{ "S12.sgn" };


	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################

	int NumberOfBits(100);

	MQamTransmitter B1{ vector<Signal*> { }, vector<Signal*> { &S1 } };
	B1.setOutputOpticalPower_dBm(0);
	B1.setMode(PseudoRandom);
	B1.setBitPeriod(1.0 / 50e9);
	B1.setPatternLength(5);
	B1.setNumberOfBits(NumberOfBits);
	B1.setIqAmplitudes({ { 1, 1 }, { -1, -1 }, { 1, -1 }, { -1, 1 } });
	B1.setNumberOfSamplesPerSymbol(16);
	B1.setRollOffFactor(0.3);
	B1.setSaveInternalSignals(false);

	BinarySource B00{ vector<Signal*> {}, vector<Signal*> { &MQAM0 } };
	B00.setMode(PseudoRandom);
	B00.setBitPeriod(1.0 / 50e9);
	B00.setPatternLength(5);
	B00.setNumberOfBits(NumberOfBits);

	discarder B000{ vector<Signal*> { &MQAM0 }, vector<Signal*> { &MQAM00 } };	

	
	MQamTransmitter B2{ vector<Signal*> { }, vector<Signal*> { &S2 } };
	B2.setOutputOpticalPower_dBm(0);
	B2.setMode(PseudoRandom);
	B2.setBitPeriod(1.0 / 50e9);
	B2.setPatternLength(5);
	B2.setNumberOfBits(NumberOfBits);
	B2.setIqAmplitudes({ { 1, 1 }, { -1, -1 }  });
	B2.setNumberOfSamplesPerSymbol(16);
	B2.setRollOffFactor(0.3);

	/*
	local_oscillator B2{ vector<Signal*> {}, vector<Signal*> { &S2 } };
	B2.setMode(PseudoRandom);
	B2.setBitPeriod(1.0 / 50e9);
	B2.setPatternLength(5);
	B2.setNumberOfBits(NumberOfBits);
	B2.setNumberOfSamplesPerSymbol(16);
	B2.setRollOffFactor(0.3);
	B2.setOutputOpticalPower_dBm(0);
	B2.setProbabilityOfZero(0);
	B2.setSaveInternalSignals(false);
	
	*/
	BalancedBeamsplitter B3{ vector<Signal*> {&S1, &S2}, vector<Signal*> {&S3, &S4} };

	photodiodeplus B4{ vector<Signal*> {&S3}, vector<Signal*> {&S5} };

	photodiodeminus B5{ vector<Signal*> {&S4}, vector<Signal*> {&S6} };

	subtractor B6{ vector<Signal*> {&S5, &S6}, vector<Signal*> {&S7} };

	TIamplifier B7{ vector<Signal*> {&S7}, vector<Signal*> {&S8} };

	discretizer B8{ vector <Signal*> {&S8}, vector<Signal*> {&S9} };

	delayer B9{ vector <Signal*> {&S9}, vector<Signal*> {&S10} };

	bit_decider B10{ vector <Signal*> {&S10}, vector<Signal*> {&S11} };

	bit_error_rate  B11{ vector <Signal*> {&S11, &MQAM00}, vector<Signal*> { &S12 } };

	Sink B12{ vector<Signal*> { &S12 }, vector<Signal*> {} };
	B12.setNumberOfSamples(5000);
	B12.setDisplayNumberOfSamples(true);

	// #####################################################################################################
	// ########################### System Declaration and Inicialization ###################################
	// #####################################################################################################

	System MainSystem{ vector<Block*> { &B00, &B000, &B1, &B2, &B3, &B4, &B5, &B6, &B7, &B8, &B9, &B10, &B11, &B12 } };

	// #####################################################################################################
	// #################################### System Run #####################################################
	// #####################################################################################################
	
	MainSystem.run();

	return 0;

}