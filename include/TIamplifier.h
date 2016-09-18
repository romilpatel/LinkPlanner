# ifndef PROGRAM_INCLUDE_TIAMPLIFIER_H_
# define PROGRAM_INCLUDE_TIAMPLIFIER_H_

# include "netxpto.h"
# include <vector>

// Simulates a Transimpedance Amplifier
class TIamplifier : public Block {
public:
	TIamplifier(vector<Signal *> &InputSig, vector<Signal *> &OutputSig);
	bool runBlock(void);

	//int index = 0;

//	int setindex(int index);

private:
	//double gain = {1000, 10000, 100000, 1000000, 10000000};




};


#endif // !PROGRAM_INCLUDE_ITAMPLIFIER_H_
