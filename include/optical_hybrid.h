# ifndef PROGRAM_INCLUDE_OPTICAL_HYBRID_H_
# define PROGRAM_INCLUDE_OPTICAL_HYBRID_H_

<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil
# include "netxpto.h"
# include <iostream>
# include <complex>
# include <fstream>
# include <algorithm>
# include <array>


// Implements a Balanced BeamSplitter
class OpticalHybrid : public Block {

	bool firstTime{ true };

public:

	t_complex div = 1 / 2;
	t_complex unit = 1;
	complex<t_real> imaginary=sqrt(-1);
	array <complex<double>, 8> matrix = { { 1 / 2, 1 / 2, 1 / 2, -1 / 2, 1 / 2, sqrt(-1) / 2, 1 / 2, -sqrt(-1) / 2 } };
	
	OpticalHybrid() {};
	OpticalHybrid(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
# include <math.h>

# include "netxpto.h"

class OpticalHybrid : public Block {

	/* State Variables */


	/* Input Parameters */

	double outputOpticalPower{ 1e-3 };
	double outputOpticalWavelength{ 1550e-9 };
	double outputOpticalFrequency{ SPEED_OF_LIGHT / outputOpticalWavelength };
	//double samplingPeriod{ 0.0 };
	double powerFactor{ sqrt(0.5) }; //factor by which each output signal must be multiplied to conserve optical power

public:

	/* Methods */
	OpticalHybrid() {};
	OpticalHybrid(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig) {};
>>>>>>> AnaLuisa
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil

	void initialize(void);
	bool runBlock(void);

<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil
	void setTransferMatrix(array<complex<double>, 8> TransferMatrix) { matrix = TransferMatrix; }
	array<complex<double>, 8> const getTransferMatrix(void) { return matrix; }

private:

};


#endif // !PROGRAM_INCLUDE_OPTICAL_HYBRID_H_
<<<<<<< HEAD
<<<<<<< HEAD
=======
=======
	void setOutputOpticalPower(double outOpticalPower) { outputOpticalPower = outOpticalPower; }
	void setOutputOpticalPower_dBm(double outOpticalPower_dBm) { outputOpticalPower = 1e-3*pow(10, outOpticalPower_dBm / 10); }

	void setOutputOpticalWavelength(double outOpticalWavelength) { outputOpticalWavelength = outOpticalWavelength; outputOpticalFrequency = SPEED_OF_LIGHT / outOpticalWavelength; }
	void setOutputOpticalFrequency(double outOpticalFrequency) { outputOpticalFrequency = outOpticalFrequency; outputOpticalWavelength = outOpticalFrequency / outputOpticalFrequency; }

	void setPowerFactor(double pFactor) { powerFactor = pFactor; };
};

#endif 
>>>>>>> AnaLuisa
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil
