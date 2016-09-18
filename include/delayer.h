# ifndef PROGRAM_INCLUDE_DELAYER_H_
# define PROGRAM_INCLUDE_DELAYER_H_

# include "netxpto.h"
# include <vector>

// Adjusts the starting point of the discretized signal
class delayer : public Block {
public:
	delayer(vector<Signal *> &InputSig, vector<Signal *> &OutputSig);
	int auxint = 0;
	bool runBlock(void);

	//int index = 0;

//	int setindex(int index);



private:





};


#endif // !PROGRAM_INCLUDE_DISCRETIZER_H_
