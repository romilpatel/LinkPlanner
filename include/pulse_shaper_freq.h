# ifndef PULSE_SHAPER_H_
# define PULSE_SHAPER_H_

# include <vector>
# include "netxpto.h"

using namespace std;

enum PulseShaperFilter { RaisedCosine };

/* Raised-cosine filter frequency implementation. */
class FD_PulseShaper : public FD_Filter{

	/* Input Parameters */
	PulseShaperFilter filterType{ RaisedCosine };
	double rollOffFactor{ 0.9 };					// Roll-off factor (roll) for the raised-cosine filter

	/* State Variable*/

public:

	/* Methods */
	FD_PulseShaper() : FD_Filter() {};
	FD_PulseShaper(vector<Signal *> &InputSig, vector<Signal *> OutputSig):FD_Filter(InputSig, OutputSig) {};

	void initialize(void);
	
	//void setTrasferFunctionLength(int tFLength){ transferFunctionLength = tFLength; };
	//int const getTransferFunctionLength(void) { return transferFunctionLength; };

	void setFilterType(PulseShaperFilter fType){ filterType = fType; };
	PulseShaperFilter const getFilterType(void){ return filterType; };

	void setRollOffFactor(double rOffFactor){ rollOffFactor = rOffFactor; };
	double const getRollOffFactor(){ return rollOffFactor; };

		
};

# endif


