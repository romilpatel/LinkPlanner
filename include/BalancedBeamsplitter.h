# ifndef PROGRAM_INCLUDE_BEAM_SPLITTER_H_
# define PROGRAM_INCLUDE_BEAM_SPLITTER_H_

# include "netxpto.h"
# include <iostream>
# include <complex>
# include <fstream>
# include <algorithm>
# include <array>


// Implements a Balanced BeamSplitter
class BalancedBeamSplitter : public Block {

	bool firstTime{ true };

public:

	double outputOpticalWavelength{ 1550e-9 };
	double outputOpticalFrequency{ SPEED_OF_LIGHT / outputOpticalWavelength };
	t_real div = 1 / sqrt(2);
	t_complex unit = 1;
	array <t_complex, 4> matrix = { { div*unit, div*unit, div*unit, -unit*div } };
	

	BalancedBeamSplitter(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};

	void initialize(void);
	bool runBlock(void);

	void setTransferMatrix(array<t_complex, 4> TransferMatrix) { matrix = TransferMatrix; }
	

	


private:
};


#endif // !PROGRAM_INCLUDE_BEAM_SPLITTER_H_
