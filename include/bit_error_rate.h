# ifndef PROGRAM_INCLUDE_BIT_ERROR_RATE_H_
# define PROGRAM_INCLUDE_BIT_ERROR_RATE_H_

# include "netxpto.h"
# include <vector>

// Calculates the BER between two binary signals
class BitErrorRate : public Block {

	bool firstTime{ true };
	
public:

	BitErrorRate(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig,OutputSig){};
	
	void initialize(void);
	bool runBlock(void);

<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil
	double coincidences = 0;
	double recievedBits = 0;

	void setConfidence(double P) { alpha = 1-P; }
	double const getConfidence(void) { return 1 - alpha; }

	void setMidReportSize(int M) { m = M; }
	int const getMidReportSize(void) { return m; }
<<<<<<< HEAD
<<<<<<< HEAD

private:
=======
=======
	long int coincidences = 0;
	long int receivedBits = 0;

	void setConfidence(t_real P) { alpha = 1-P; }
	void setMidReportSize(int M) { m = M; }
>>>>>>> AnaLuisa

private:

>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======

private:
>>>>>>> Romil
	int firstPass = 1;

	double alpha = 0.05;
	double z;
	int m = 0;
	int n = 0;
};


#endif // !PROGRAM_INCLUDE_BIT_ERROR_RATE_H_
