# ifndef PROGRAM_INCLUDE_ELECTRICAL_FILTER_H_
# define PROGRAM_INCLUDE_ELECTRICAL_FILTER_H_

# include "netxpto.h"
# include <vector>

// Implements an electrical filter
class ElectricalFilter : public Block {

	bool firstTime{ true };

public:

	int sampling = 16;
	int delay = 9;

	int AuxInt = 0;

	ElectricalFilter() {};
	ElectricalFilter(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};

	void initialize(void);
	bool runBlock(void);

	void setSamplingRate(int Sampling) { sampling = Sampling; }
	void setDelay(int Delay) { delay = Delay; }

private:





};


#endif // !PROGRAM_INCLUDE_ELECTRICAL_FILTER_H_
