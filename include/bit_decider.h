# ifndef PROGRAM_INCLUDE_BIT_DECIDER_H_
# define PROGRAM_INCLUDE_BIT_DECIDER_H_

# include "netxpto.h"
# include <vector>

// Evaluates the input signal and outputs a binary key in accordance to the input values
class BitDecider : public Block {

	/* [DIA]
	 * 
	 * Falta adicionar os dois n�veis distintos, setPosReferenceValue e
	 * setNegReferenceValue (ver documenta��o).
	 */

	double decisionLevel{ 0.0 };

public:

	BitDecider() {};
	BitDecider(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};
	
	void initialize(void);
	bool runBlock(void);

	void setDecisionLevel(double dLevel) { decisionLevel = dLevel; }
	double getDecisionLevel(void) { return decisionLevel; }

};


#endif // !PROGRAM_INCLUDE_BIT_DECIDER_H_
