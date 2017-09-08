# ifndef PROGRAM_INCLUDE_SAMPLER_H_
# define PROGRAM_INCLUDE_SAMPLER_H_

# include "netxpto.h"
# include <vector>

// Takes a sampling of the input electrical signal
class Sampler : public Block {

	bool firstTime{ true };

<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil
	bool firstPass{ true };
	bool repeatedPass{ false };
	int samplesToSkip{ 0 };
	int count = 0;
	bool aux1{ false };
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> Romil

public:

	Sampler() {};
	Sampler(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){};
<<<<<<< HEAD
=======
=======
	//int sampling = 16;

	//int delay = 9;

	//int AuxInt = 0;

	t_integer samplesToSkip{ 0 };
>>>>>>> AnaLuisa


public:

	double outputOpticalPower{ 1e-3 };
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil

	void initialize(void);
	bool runBlock(void);

<<<<<<< HEAD
<<<<<<< HEAD
	void setSamplesToSkip(int sToSkip) { samplesToSkip = sToSkip; }
	int const getSamplesToSkip(void) { return samplesToSkip; }
=======
<<<<<<< HEAD
	void setSamplesToSkip(int sToSkip) { samplesToSkip = sToSkip; }
	int const getSamplesToSkip(void) { return samplesToSkip; }
=======
	Sampler() {};
	Sampler(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig) {};

	//void setSamplingRate(int Sampling) { sampling = Sampling; }
	//void setDelay(int Delay) { delay = Delay; }
	void setSamplesToSkip(t_integer sToSkip) { samplesToSkip = sToSkip; }
	void setOutputOpticalPower(double outOpticalPower) { outputOpticalPower = outOpticalPower; }
	void setOutputOpticalPower_dBm(double outOpticalPower_dBm) { outputOpticalPower = 1e-3*pow(10, outOpticalPower_dBm / 10); }

>>>>>>> AnaLuisa
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
	void setSamplesToSkip(int sToSkip) { samplesToSkip = sToSkip; }
	int const getSamplesToSkip(void) { return samplesToSkip; }
>>>>>>> Romil

};


#endif // !PROGRAM_INCLUDE_SAMPLER_H_
