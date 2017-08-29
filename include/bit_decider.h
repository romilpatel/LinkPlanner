# ifndef PROGRAM_INCLUDE_BIT_DECIDER_H_
# define PROGRAM_INCLUDE_BIT_DECIDER_H_

# include "netxpto.h"
# include <vector>

// Evaluates the input signal and outputs a binary key in accordance to the input values
class BitDecider : public Block {

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> Romil
	/* [DIA]
	 * 
	 * Falta adicionar os dois níveis distintos, setPosReferenceValue e
	 * setNegReferenceValue (ver documentação).
	 */

<<<<<<< HEAD
=======
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil
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
