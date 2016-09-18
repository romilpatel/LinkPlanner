# ifndef BPSK_MAPPER_H_
# define BPSK_MAPPER_H_

# include <vector>
#include <math.h>       // log2 

# include "..\include\netxpto.h"

using namespace std;


/* Realizes the Binary Phase Shift Keying mapping. */
class bpsk_mapper : public Block {
public:
	bpsk_mapper(vector<Signal *> &InputSig, vector<Signal *> &OutputSig);

	bool runBlock(void);

	void setM(int mValue) { m = mValue; };		// m should be of the form m = 2^n, with n integer;

private:
	t_real amplitude{ 1 };
	t_integer m{ 4 };
	t_binary *binaryValue = new t_binary[(int)log2(m)];
	int auxBinaryValue{ 0 };;
};

#endif
