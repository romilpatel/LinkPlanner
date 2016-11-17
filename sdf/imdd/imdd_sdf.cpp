# include "netxpto.h"

# include "binary_source.h"
# include "discrete_to_continuous_time.h"
# include "pulse_shaper.h"
# include "im_modulator.h"
# include "fiber.h"
# include "pin.h"
# include "sink.h"

int main() {

	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	Binary S1{ "S1.sgn" };

	TimeContinuousAmplitudeDiscreteReal S2{ "S2.sgn" };

	TimeContinuousAmplitudeContinuousReal S3{ "S3.sgn" };

	OpticalSignal S4{ "S4.sgn" };

	OpticalSignal S5{ "S5.sgn" };

	TimeContinuousAmplitudeContinuousReal S6{ "S6.sgn" };

	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################


	BinarySource B1{ vector<Signal*> {}, vector<Signal*> { &S1 } };
	B1.setMode(DeterministicAppendZeros);
	B1.setBitPeriod(1.0 / 50e9);
	B1.setBitStream("0000000001000000000");
	//B1.setPatternLength(5);
	//B1.setNumberOfBits(10000);

	DiscreteToContinuousTime B2{ vector<Signal*> { &S1 }, vector<Signal*> { &S2 } };
	B2.setNumberOfSamplesPerSymbol(16);

	PulseShaper B3{ vector<Signal*> { &S2 }, vector<Signal*> { &S3 } };
	B3.setRollOffFactor(0.3);
	B3.setImpulseResponseTimeLength(16);
	B3.setSeeBeginningOfImpulseResponse(false);

	ImModulator B4{ vector<Signal*> { &S3 }, vector<Signal*> { &S4 } };
	B4.outputOpticalPower = 1e-3;

	Fiber B5{ vector<Signal*> { &S4 }, vector<Signal*> { &S5 } };
	B5.fiberLength = 50e3;

	Pin B6{ vector<Signal*> { &S5 }, vector<Signal*> { &S6 } };

	Sink B7{ vector<Signal*> { &S6 }, vector<Signal*> {} };
	B7.setNumberOfSamples(5000);
	B7.setDisplayNumberOfSamples(true);

	// #####################################################################################################
	// ########################### System Declaration and Inicialization ###################################
	// #####################################################################################################

	System MainSystem{ vector<Block*> { &B1, &B2, &B3, &B4, &B5, &B6, &B7 } };

	// #####################################################################################################
	// #################################### System Run #####################################################
	// #####################################################################################################

	MainSystem.run();

	return 0;

}