# ifndef PROGRAM_INCLUDE_PHOTODIODEPLUS_H_
# define PROGRAM_INCLUDE_PHOTODIODEPLUS_H_

# include "netxpto.h"

// Simulates a photodiode
class photodiodeplus : public Block {
public:
	photodiodeplus(vector<Signal *> &InputSig, vector<Signal *> &OutputSig);
	bool runBlock(void);

private:

};


#endif // !PROGRAM_INCLUDE_PHOTODIODEPLUS_H_
