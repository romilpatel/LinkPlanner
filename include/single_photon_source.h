# ifndef SINGLE_PHOTON_SOURCE_H_
# define SINGLE_PHOTON_SOURCE_H_


class SinglePhotonSource : public Block {

	/* input parameters */
	vector<t_real> polarization{ 0 };
	signal_value_type inputSignalValueType;

public:

	SinglePhotonSource(vector<Signal *> &inputSignals, vector<Signal *> &outputSignals) : Block(inputSignals, outputSignals){};

	void initialize(void);

	bool runBlock(void);
		
	void setPolarization(vector<t_real> pol){ polarization = pol; };
	vector<t_real> getPolarization() { return polarization; };
};

#endif