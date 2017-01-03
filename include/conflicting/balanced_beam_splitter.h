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

<<<<<<< HEAD
	double outputOpticalWavelength{ 1550e-9 };
	double outputOpticalFrequency{ SPEED_OF_LIGHT / outputOpticalWavelength };
	t_real F = 1 / sqrt(2);
	t_complex unit = 1;
	array <t_complex, 4> matrix = { { F*unit, F*unit, F*unit, -unit*F } };
	t_real mode = 0 ;


	BalancedBeamSplitter(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig) {};
=======
	//double outputOpticalWavelength{ 1550e-9 };
	//double outputOpticalFrequency{ SPEED_OF_LIGHT / outputOpticalWavelength };
	t_real div = 1 / sqrt(2);
	t_complex unit = 1;
	array <t_complex, 4> matrix = { { div*unit, div*unit, div*unit, -unit*div } };
	
	BalancedBeamSplitter() {};
	BalancedBeamSplitter(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};
>>>>>>> dc00d875a4698894f7854fe56be177086bf2b48b

	void initialize(void);
	bool runBlock(void);

	void setTransferMatrix(array<t_complex, 4> TransferMatrix) { matrix = TransferMatrix; }
<<<<<<< HEAD

	void setMode(t_real Mode) { mode = Mode; }


private:
=======
	
private:

>>>>>>> dc00d875a4698894f7854fe56be177086bf2b48b
};


#endif // !PROGRAM_INCLUDE_BEAM_SPLITTER_H_
<<<<<<< HEAD

=======
>>>>>>> dc00d875a4698894f7854fe56be177086bf2b48b
