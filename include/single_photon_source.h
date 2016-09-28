# ifndef SINGLE_PHOTON_SOURCE_H_
# define SINGLE_PHOTON_SOURCE_H_


class SinglePhotonSource : public Block {

	/* input parameters */
	t_real polarization{ 0 };

public:

	SinglePhotonSource(vector<Signal *> &inputSignals, vector<Signal *> &outputSignals) : Block(inputSignals, outputSignals){};

	void initialize(void);

	bool runBlock(void);
		
	void setPolarization(t_real pol){ polarization = pol; };
	t_real getPolarization() { return polarization; };
};

#endif