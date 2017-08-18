# ifndef SINGLE_PHOTON_DETECTOR_H_
# define SINGLE_PHOTON_DETECTOR_H_

# include "netxpto.h"

class SinglePhotonDetector : public Block {
	
	// Input Parameters
	t_integer path{ 0 };

public:

	SinglePhotonDetector(vector<Signal *> &inputSignals, vector<Signal *> &outputSignals) : Block(inputSignals, outputSignals){};

	void initialize(void);

	bool runBlock(void);

	void setPath(t_integer p) { path = p; };
	t_integer getPath() { return path; };
		
};

#endif