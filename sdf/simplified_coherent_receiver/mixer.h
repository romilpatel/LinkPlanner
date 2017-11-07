# ifndef PROGRAM_FOR_MIXER_H_
# define PROGRAM_FOR_MIXER_H_

# include <vector>
# include "netxpto.h"

using namespace std;



class mixer : public Block
{
	/* Input Parameters */

public:
	/* Methods */
	mixer() {};
	mixer(vector<Signal *> &InputSig, vector<Signal *> OutputSig) :Block(InputSig, OutputSig) {};
	void initialize(void);
	bool runBlock(void);


};
# endif


