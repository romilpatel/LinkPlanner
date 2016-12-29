# ifndef PROGRAM_INCLUDE_ADD_H_
# define PROGRAM_INCLUDE_ADD_H_

# include "netxpto.h"

// Simulates a simple adding block 
class Add : public Block {

	bool firstTime{ true };

public:

	bool opticalNoise = false;

	Add() {};
	Add(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};
	
	void initialize(void);
	bool runBlock(void);

	void useNoise(bool oNoise) { opticalNoise = oNoise; }
	
private:
};


#endif _
