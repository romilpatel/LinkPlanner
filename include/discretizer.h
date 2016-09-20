# ifndef PROGRAM_INCLUDE_DISCRETIZER_H_
# define PROGRAM_INCLUDE_DISCRETIZER_H_

# include "netxpto.h"
# include <vector>

// Takes a sampling of the input electrical signal
class discretizer : public Block {

	bool firstTime{ true };

public:
	discretizer(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};

	void initialize(void);
	bool runBlock(void);


//	int setindex(int index);



private:





};


#endif // !PROGRAM_INCLUDE_DISCRETIZER_H_
