# include "netxpto.h"

# include "binary_source.h"
//# include "discrete_to_continuous_time.h"
# include "single_photon_source.h"
//# include "polarization_beam_splitter.h"
//# include "single_photon_detector.h"
//# include "qrng_decision_circuit.h"
# include "sink.h"

int main(){

	// #####################################################################################################
	// ########################### Signals Declaration and Inicialization ##################################
	// #####################################################################################################
	
	Binary S1{ "S1.sgn" };

	Binary S2{ "S2.sgn" };

	//Binary S3{ "S3.sgn" };

	//TimeContinuousAmplitudeDiscreteReal S4{ "S2.sgn" };

	PhotonStream S3{};

	//PhotonStream S6{};

	//TimeContinuousAmplitudeDiscreteReal S5{ "S5.sgn" };

	//TimeContinuousAmplitudeDiscreteReal S6{ "S6.sgn" };
	
	//Binary S7{ "S7.sgn" };

	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################


	BinarySource B1{ vector<Signal*> {}, vector<Signal*> { &S1 } };
	B1.setMode(DeterministicAppendZeros);
	B1.setBitPeriod(1.0 / 1e3);
	B1.setBitStream("10010110");
	B1.setNumberOfBits(10);
	
	BinarySource B2{ vector<Signal*> {}, vector<Signal*> { &S2 } };
	B2.setMode(DeterministicAppendZeros);
	B2.setBitPeriod(1.0 / 1e3);
	B2.setBitStream("00101110");
	B2.setNumberOfBits(10);

	SinglePhotonSource B3{ vector<Signal*> { &S1, &S2 }, vector<Signal*> { &S3} };
	B3.setPolarization({ 0, -45, 90, 45 });

	/*PolarizationBeamSplitter B4{ vector<Signal*> { &S3 }, vector<Signal*> { &S4} };

	SinglePhotonDetector B5{ vector<Signal*> { &S4 }, vector<Signal*> { &S5} };
	B5.setPath(0);

	SinglePhotonDetector B6{ vector<Signal*> { &S4 }, vector<Signal*> { &S6} };
	B6.setPath(1);

	QRNG_DecisionCircuit B7{ vector<Signal*> { &S5, &S6 }, vector<Signal*> { &S7} };*/
	
	Sink B4{ vector<Signal*> { &S3 }, vector<Signal*> {} };
	B4.setNumberOfSamples(10);
	B4.setDisplayNumberOfSamples(true);

	// #####################################################################################################
	// ########################### System Declaration and Inicialization ###################################
	// #####################################################################################################

	System MainSystem{ vector<Block*> { &B1, &B2, &B3, &B4 } }; // , &B5, &B6, &B7, &B8 }

	// #####################################################################################################
	// #################################### System Run #####################################################
	// #####################################################################################################
	
	MainSystem.run();

	return 0;

}