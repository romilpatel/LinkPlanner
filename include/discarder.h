# ifndef PROGRAM_INCLUDE_DISCARDER_H_
# define PROGRAM_INCLUDE_DISCARDER_H_

# include "netxpto.h"
# include <vector>

// Adjusts the starting point of the discretized signal
class discarder : public Block {
public:
	discarder(vector<Signal *> &InputSig, vector<Signal *> &OutputSig);
	bool runBlock(void);

	//int index = 0;

//	int setindex(int index);



private:





};


#endif // !PROGRAM_INCLUDE_DISCARDER_H_
