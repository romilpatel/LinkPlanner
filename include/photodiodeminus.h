# ifndef PROGRAM_INCLUDE_PHOTODIODEMINUS_H_
# define PROGRAM_INCLUDE_PHOTODIODEMINUS_H_

# include "netxpto.h"

// Simulates a photodiode
class photodiodeminus : public Block {
public:
	photodiodeminus(vector<Signal *> &InputSig, vector<Signal *> &OutputSig);
	bool runBlock(void);


	//t_integer sign{ 1 };
	t_real SIGN;

	t_real setsign( int sign );
	
private:

};


#endif // !PROGRAM_INCLUDE_PHOTODIODE_H_
