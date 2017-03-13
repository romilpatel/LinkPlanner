# ifndef PULSE_SHAPER_H_
# define PULSE_SHAPER_H_

# include <vector>
# include "netxpto.h"

using namespace std;

enum PulseShaperFilter { RaisedCosine };

/* Raised-cosine filter frequency implementation. */
class PulseShaper : public Block{

	/* Input Parameters */
	PulseShaperFilter filterType{ RaisedCosine };

	int transferFunctionLength{ 16 };				

	double rollOffFactor{ 0.9 };					// Roll-off factor (roll) for the raised-cosine filter

	/* State Variable*/
	vector<t_complex> transferFunction { transferFunctionLength, 0.0 };

	vector<t_real> inSigTime;

	vector<t_real> OutSigTime;

public:

	/* Methods */
	PulseShaper() {};
	PulseShaper(vector<Signal *> &InputSig, vector<Signal *> OutputSig);

	void initialize(void);
	void run(void);
	
	void setTrasferFunctionLength(int tFLength){ transferFunctionLength = tFLength; };
	int const getTransferFunctionLength(void) { return transferFunctionLength; };

	void setFilterType(PulseShaperFilter fType){ filterType = fType; };
	PulseShaperFilter const getFilterType(void){ return filterType; };

	void setRollOffFactor(double rOffFactor){ rollOffFactor = rOffFactor; };
	double const getRollOffFactor(){ return rollOffFactor; };

		
};

# endif


