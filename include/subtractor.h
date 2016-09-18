# ifndef PROGRAM_INCLUDE_SUBTRACTOR_H_
# define PROGRAM_INCLUDE_SUBTRACTOR_H_

# include "netxpto.h"

// Simulates a subtractor
class subtractor : public Block {
public:
	subtractor(vector<Signal *> &InputSig, vector<Signal *> &OutputSig);
	bool runBlock(void);
	
private:
	//t_complex div{ 1 / sqrt(2) };
	//double phase{ PI / 2 };
};


#endif // !PROGRAM_INCLUDE_SUBTRACTOR_H_
