# ifndef LOCAL_OSCILLATOR_H_
# define LOCAL_OSCILLATOR_H_

# include "netxpto.h"
# include "binary_source.h"
# include "bpsk_mapper.h"
# include "discrete_to_continuous_time.h"
# include "pulse_shaper.h"
# include "BPSKMODULATOR.h"

//using namespace std;


class local_oscillator : public Block {

	/* State Variables */

	// #####################################################################################################
	// ################## Internal Signals Declaration and Inicialization ##################################
	// #####################################################################################################

	Binary S1;

	TimeDiscreteAmplitudeDiscreteReal S2;

	TimeContinuousAmplitudeDiscreteReal S3;

	TimeContinuousAmplitudeContinuousReal S4;

	BandpassSignal S5;


	// #####################################################################################################
	// ########################### Blocks Declaration and Inicialization ###################################
	// #####################################################################################################


	BinarySource B1{ vector<Signal*> {}, vector<Signal*> { &S1 } };

	bpsk_mapper B2{ vector<Signal*> { &S1 }, vector<Signal*> { &S2, &S3 } };

	DiscreteToContinuousTime B3{ vector<Signal*> { &S2 }, vector<Signal*> { &S4 } };

	PulseShaper B4{ vector<Signal*> { &S3 }, vector<Signal*> { &S4 } };

	BPSKMODULATOR B5{ vector<Signal*> { &S4 }, vector<Signal*> { &S5 } };


	vector<Block*> ModuleBlocks;
	bool firstTime{ true };
	int buffersLength{ 512 };

public:

	/* Input Parameters */

	bool saveInternalSignals{ true };

	/* Methods */

	local_oscillator(vector<Signal *> &InputSig, vector<Signal *> &OutputSig);
	~local_oscillator(void);

	bool runBlock(void);

	/* Set Methods */

	void setMode(BinarySourceMode m) { B1.mode = m; }
	void setProbabilityOfZero(double pZero) { B1.probabilityOfZero = pZero; }
	void setBitStream(string bStream) { B1.bitStream = bStream; }
	void setNumberOfBits(long int nOfBits) { B1.numberOfBits = nOfBits; }
	void setPatternLength(int pLength) { B1.patternLength = pLength; }
	void setBitPeriod(double bPeriod);
	void setBuffersLength(int bLength);
	
	void setNumberOfSamplesPerSymbol(int n);

	void setRollOffFactor(double rOffFactor){ B4.setRollOffFactor(rOffFactor); };

	void setOutputOpticalPower(t_real outOpticalPower) { B5.outputOpticalPower = outOpticalPower; };
	void setOutputOpticalPower_dBm(t_real outOpticalPower_dBm) { B5.outputOpticalPower = 1e-3*pow(10, outOpticalPower_dBm / 10); };

	void setSaveInternalSignals(bool sSignals);

};

#endif