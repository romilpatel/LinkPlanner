# ifndef PROGRAM_INCLUDE_BEAM_SPLITTER_H_
# define PROGRAM_INCLUDE_BEAM_SPLITTER_H_

# include "netxpto.h"

// Implements a Balanced BeamSplitter
class BalancedBeamsplitter : public Block {
public:
	BalancedBeamsplitter(vector<Signal *> &InputSig, vector<Signal *> &OutputSig);
	bool runBlock(void);
private:
	t_complex div{ 1 / sqrt(2) };
};


#endif // !PROGRAM_INCLUDE_BEAM_SPLITTER_H_
