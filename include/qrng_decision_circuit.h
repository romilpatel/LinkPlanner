# ifndef QNRG_DECISION_CIRCUIT_H_
# define QNRG_DECISION_CIRCUIT_H_

class QRNG_DecisionCircuit : public Block {

	/* input parameters */

public:

	QRNG_DecisionCircuit(vector<Signal *> &inputSignals, vector<Signal *> &outputSignals) : Block(inputSignals, outputSignals){};

	void initialize(void);

	bool runBlock(void);

};

#endif