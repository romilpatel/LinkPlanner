# ifndef PROGRAM_INCLUDE_BIT_DECIDER_H_
# define PROGRAM_INCLUDE_BIT_DECIDER_H_

# include "netxpto.h"
# include <vector>

// Adjusts the starting point of the discretized signal
class bit_decider : public Block {
public:
	bit_decider(vector<Signal *> &InputSig, vector<Signal *> &OutputSig);
	bool runBlock(void);

	//int index = 0;

//	int setindex(int index);



private:





};


#endif // !PROGRAM_INCLUDE_DISCRETIZER_H_
