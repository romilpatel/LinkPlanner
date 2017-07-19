# ifndef ELECTRICAL_FILTER_H_
# define ELECTRICAL_FILTER_H_

# include "netxpto.h"

using namespace std;

enum Filter { LowPass };

class ElectricalFilter : public FIR_Filter {

	Filter filterType{ LowPass };

	int impulseResponseTimeLength{ 16 };

	double cutoffFrequency{ 5 }; //hertz

public:

	ElectricalFilter() :FIR_Filter() {};
	ElectricalFilter(vector<Signal *> &InputSig, vector<Signal *> OutputSig) :FIR_Filter(InputSig, OutputSig) {};

	void initialize(void);

	void setImpulseResponseTimeLength(int impResponseTimeLength) { impulseResponseTimeLength = impResponseTimeLength; };
	int const getImpulseResponseTimeLength(void) { return impulseResponseTimeLength; };

	void setCutoffFrequency(double cOffFrequency) { cutoffFrequency = cOffFrequency; };
	double const getCutoffFrequency() { return cutoffFrequency; };

	void setFilterType(Filter fType) { filterType = fType; };
	Filter const getFilterType(void) { return filterType; };

};
#endif