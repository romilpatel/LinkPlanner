# include "netxpto.h"

# include "binary_source.h"
# include "m_qam_mapper.h"
# include "discrete_to_continuous_time.h"
# include "pulse_shaper.h"
# include "iq_modulator.h"
# include "sink.h"

int main() {

	// #####################################################################################################
	// ################################### System Input Parameters #########################################
	// #####################################################################################################

	BinarySourceMode sourceMode{ PseudoRandom };				
	int patternLength{ 5 };
	string bitStream{ "0" };
	double bitPeriod{ 1.0 / 50e9 };
	vector<t_iqValues> iqAmplitudes{ { { 0,0 },{ 1,0 },{ 2,0 },{ 3,0 } } };
	//vector<t_iqValues> iqAmplitudes{ { { -3.0, -3.0 }, { -3.0, -1.0 }, { -3.0, 3.0 }, { -3.0, 1.0 }, { -1.0, -3.0 }, { -1.0, -1.0 }, { -1.0, 3.0 }, { -1.0, 1.0 }, { 3.0, -3.0 }, { 3.0, -1.0 }, { 3.0, 3.0 }, { 3.0, 1.0 }, { 1.0, -3.0 }, { 1.0, -1.0 }, { 1.0, 3.0 }, { 1.0, 1.0 } } };
	int numberOfBits{ 1000 };				// For value of {-1}, it'll generate long bit sequence.
	int numberOfSamplesPerSymbol{ 16 };
	double rollOffFactor{ 0.3 };
	int impulseResponseTimeLength{ 16 };

	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	Binary S1{ "S1.sgn" };										// Binary Sequence
	TimeDiscreteAmplitudeDiscreteReal S2{ "S2.sgn" };			// MPAM Mapping
	TimeContinuousAmplitudeDiscreteReal S3{ "S3.sgn" };			// Discrete to continious time
	TimeContinuousAmplitudeContinuousReal S4{ "S4.sgn" };		// Pulse Shapping filter
	BandpassSignal S5{ "S5.sgn" };								// Oscillator
	BandpassSignal S6{ "S6.sgn" };								// Mixer	
	BandpassSignal S7{ "S7.sgn" };								// Fork_s7
	BandpassSignal S8{ "S8.sgn" };								// Fork_s8
	BandpassSignal S9{ "S9.sgn" };								// Hilbert Transformer
	BandpassSignal S10{ "S10.sgn" };							// IQ Modulator
	
	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################

	BinarySource B1{ vector<Signal*> {}, vector<Signal*> { &S1} };
	B1.setMode(sourceMode);
	B1.setPatternLength(patternLength);
	B1.setBitStream(bitStream);
	B1.setBitPeriod(bitPeriod);
	B1.setNumberOfBits(numberOfBits);

	MPamMapper B2{ vector<Signal*> { &S1 }, vector<Signal*> { &S2} };
	B2.setIqAmplitudes(iqAmplitudes);

	DiscreteToContinuousTime B3{ vector<Signal*> { &S2 }, vector<Signal*> { &S3 } };
	B3.setNumberOfSamplesPerSymbol(numberOfSamplesPerSymbol);

	//DiscreteToContinuousTime B4{ vector<Signal*> { &S3 }, vector<Signal*> { &S5 } };
	//B4.setNumberOfSamplesPerSymbol(numberOfSamplesPerSymbol);

	PulseShaper B5{ vector<Signal*> { &S4 }, vector<Signal*> { &S6 } };
	B5.setRollOffFactor(rollOffFactor);
	B5.setImpulseResponseTimeLength(impulseResponseTimeLength);
	B5.setSeeBeginningOfImpulseResponse(false);

	PulseShaper B6{ vector<Signal*> { &S5 }, vector<Signal*> { &S7 } };
	B6.setRollOffFactor(rollOffFactor);
	B6.setImpulseResponseTimeLength(impulseResponseTimeLength);
	B6.setSeeBeginningOfImpulseResponse(false);

	IqModulator B7{ vector<Signal*> { &S6, &S7 }, vector<Signal*> { &S8 } };

	Sink B8{ vector<Signal*> { &S8 }, vector<Signal*> {} };
	//B8.setNumberOfSamples(5000);
	//B8.setDisplayNumberOfSamples(true);

	Sink B9{ vector<Signal*> { &S9 }, vector<Signal*> {} };

	// #####################################################################################################
	// ########################### System Declaration and Inicialization ###################################
	// #####################################################################################################

	System MainSystem{ vector<Block*> { &B1, &B2, &B3, &B4, &B5, &B6, &B7, &B8 } };

	// #####################################################################################################
	// #################################### System Run #####################################################
	// #####################################################################################################

	MainSystem.run();

	return 0;

}