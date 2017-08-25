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
<<<<<<< HEAD
=======
<<<<<<< HEAD
	t_real div = 1 / sqrt(2);
	t_complex unit = 1;
	array <complex<double>, 4> matrix = { { div*unit, div*unit, div*unit, -unit*div } };
	
=======
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil
	double outputOpticalWavelength{ 1550e-9 };
	double outputOpticalFrequency{ SPEED_OF_LIGHT / outputOpticalWavelength };
	t_real F = 1 / sqrt(2);
	t_complex unit = 1;
	array <t_complex, 4> matrix = { { F*unit, F*unit, F*unit, -unit*F } };
	t_real mode = 0 ;

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> AnaLuisa
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil
	BalancedBeamSplitter() {};
	BalancedBeamSplitter(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig) {};

	void initialize(void);
	bool runBlock(void);

<<<<<<< HEAD
<<<<<<< HEAD
//	void setTransferMatrix(array<complex<double>, 4> TransferMatrix) { matrix = TransferMatrix; }
//	array<complex<double>, 4> const getTransferMatrix(void) { return matrix; }

=======
<<<<<<< HEAD
	void setTransferMatrix(array<complex<double>, 4> TransferMatrix) { matrix = TransferMatrix; }
	array<complex<double>, 4> const getTransferMatrix(void) { return matrix; }
=======
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
//	void setTransferMatrix(array<complex<double>, 4> TransferMatrix) { matrix = TransferMatrix; }
//	array<complex<double>, 4> const getTransferMatrix(void) { return matrix; }

>>>>>>> Romil
	void setTransferMatrix(array<t_complex, 4> TransferMatrix) { matrix = TransferMatrix; }


	void setMode(t_real Mode) { mode = Mode; }

<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> AnaLuisa

>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil
private:

};


#endif // !PROGRAM_INCLUDE_BEAM_SPLITTER_H_

