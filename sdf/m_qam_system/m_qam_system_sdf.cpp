# include "m_qam_transmitter.h"
# include "sink.h"

int main(){

	// #####################################################################################################
	// #################################### System Input Parameters ########################################
	// #####################################################################################################

	t_integer numberOfBitsGenerated(40);
	t_integer samplesPerSymbol(32);
	t_integer pLength = 5;
	t_real bitPeriod = 1.0 / 50e9;
	t_real rollOffFactor = 0.3;
	vector<t_iqValues> iqAmplitudeValues = { { -1, 0 },{ 1, 0 } };
	t_real signalOutputPower_dBm = -20;


	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################
	
	OpticalSignal S1("S1.sgn");
	Binary S2("S2.sgn");

	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################


	MQamTransmitter B1{ vector<Signal*> {}, vector<Signal*> { &S1, &S2 } };
	B1.setNumberOfBits(numberOfBitsGenerated);
	B1.setOutputOpticalPower_dBm(signalOutputPower_dBm);
	//B1.setMode(PseudoRandom);
	B1.setMode(DeterministicAppendZeros);
	B1.setBitStream("010");
	B1.setBitPeriod(bitPeriod);
	B1.setPatternLength(pLength);
	B1.setIqAmplitudes(iqAmplitudeValues);
	B1.setNumberOfSamplesPerSymbol(samplesPerSymbol);
	B1.setRollOffFactor(rollOffFactor);
	B1.setSaveInternalSignals(true);
	B1.setSeeBeginningOfImpulseResponse(true);

	Sink B2{ vector<Signal*> { &S1 }, vector<Signal*> {} };
	B2.setDisplayNumberOfSamples(true);

	Sink B3{ vector<Signal*> { &S2 }, vector<Signal*> {} };
	B3.setDisplayNumberOfSamples(true);

	// #####################################################################################################
	// ########################### System Declaration and Inicialization ###################################
	// #####################################################################################################

	System MainSystem{ vector<Block*> { &B1, &B2, &B3 } };
	//System MainSystem{ vector<Block*> { &B1, &B2 } };

	// #####################################################################################################
	// #################################### System Run #####################################################
	// #####################################################################################################
	
	MainSystem.run();

	return 0;

}
