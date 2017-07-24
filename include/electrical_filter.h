# ifndef PROGRAM_INCLUDE_ELECTRICAL_FILTER_H_
# define PROGRAM_INCLUDE_ELECTRICAL_FILTER_H_

# include "netxpto.h"
# include <vector>

using namespace std;

enum  ElectricalShapeFilter { RaisedCosine1 };

// Implements an electrical filter
class ElectricalFilter : public FIR_Filter {

	ElectricalShapeFilter filterType{ RaisedCosine1 };

	int impulseResponseTimeLength{ 16 };

	double rollOffFactor{ 0.9 };


public:

	ElectricalFilter() :FIR_Filter(){};
	ElectricalFilter(vector<Signal*> &InputSig, vector<Signal*> OutputSig) :FIR_Filter(InputSig, OutputSig){};

	void initialize(void);

	void setImpulseResponseTimeLength(int impResponseTimeLength){ impulseResponseTimeLength = impResponseTimeLength; };
	int const getImpulseResponseTimeLength(void) { return impulseResponseTimeLength; };

	void setFilterType(ElectricalShapeFilter fType){ filterType = fType; };
	ElectricalShapeFilter const getFilterType(void){ return filterType; };

	void setRollOffFactor(double rOffFactor){ rollOffFactor = rOffFactor; };
	double const getRollOffFactor(){ return rollOffFactor; };

};


#endif // !PROGRAM_INCLUDE_ELECTRICAL_FILTER_H_
