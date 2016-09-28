# include "sink.h"
# include "BalancedBeamsplitter.h"
# include "subtractor.h"
# include "photodiode.h"
# include "TIamplifier.h"
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
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	Binary MQAM0{ "MQAM0.sgn" };

	OpticalSignalXY S01("S01.sgn");

	OpticalSignalXY S02("S02.sgn");

	BandpassSignal S03("S03.sgn");

	BandpassSignal S04("S04.sgn");

	TimeContinuousAmplitudeContinuousReal S05{ "S05.sgn" };

	TimeContinuousAmplitudeContinuousReal S06{ "S06.sgn" };

	TimeContinuousAmplitudeContinuousReal S07{ "S07.sgn" };

	TimeContinuousAmplitudeContinuousReal S08{ "S08.sgn" };

	TimeDiscreteAmplitudeContinuousReal S09{ "S09.sgn" };

	TimeDiscreteAmplitudeContinuousReal S10{ "S10.sgn" };

	Binary S11{ "S11.sgn" };

	Binary S12{ "S12.sgn" };


	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################

	int NumberOfBits(1e3);

	BinarySource B00{ vector<Signal*> {}, vector<Signal*> { &MQAM0 } };
	B00.setMode(PseudoRandom);
	B00.setBitPeriod(1.0 / 50e9);
	B00.setPatternLength(5);
	B00.setNumberOfBits(NumberOfBits);

	//discarder B000{ vector<Signal*> { &MQAM0 }, vector<Signal*> { &MQAM00 } };

	MQamTransmitter B1{ vector<Signal*> { }, vector<Signal*> { &S01 } };
	B1.setOutputOpticalPower_dBm(0);
	B1.setMode(PseudoRandom);
	B1.setBitPeriod(1.0 / 50e9);
	B1.setPatternLength(5);
	B1.setNumberOfBits(NumberOfBits);
	B1.setIqAmplitudes({ { 1, 1 }, { -1, -1 } });
	B1.setNumberOfSamplesPerSymbol(16);
	B1.setRollOffFactor(0.3);
	B1.setSaveInternalSignals(false);

	local_oscillator B2{ vector<Signal*> { &S01 }, vector<Signal*> { &S02 } };

	BalancedBeamsplitter B3{ vector<Signal*> { &S02 }, vector<Signal*> { &S03,&S04 } };

	photodiode B4{ vector<Signal*> { &S03,&S04 }, vector<Signal*> { &S05, &S06 } };

	subtractor B5{ vector<Signal*> { &S05, &S06 }, vector<Signal*> { &S07 } };

	TIamplifier B6{ vector<Signal*> { &S07 }, vector<Signal*> { &S08 } };

	discretizer B7 {vector<Signal*> { &S08 }, vector<Signal*> { &S09 } };

	delayer B8{ vector<Signal*> { &S09 }, vector<Signal*> { &S10 } };

	bit_decider B9{ vector<Signal*> { &S10 }, vector<Signal*> { &S11 } };

	bit_error_rate B10{ vector<Signal*> { &S11, &MQAM0 }, vector<Signal*> { &S12 } };

	Sink B11{ vector<Signal*> { &S12 }, vector<Signal*> {} };
	B11.setNumberOfSamples(50000);
	B11.setDisplayNumberOfSamples(true);

	// #####################################################################################################
	// ########################### System Declaration and Inicialization ###################################
	// #####################################################################################################

	System MainSystem{ vector<Block*> { &B00, &B1, &B2, &B3, &B4, &B5, &B6, &B7, &B8, &B9, &B10, &B11} };

	// #####################################################################################################
	// #################################### System Run #####################################################
	// #####################################################################################################
	
	MainSystem.run();

	return 0;

}