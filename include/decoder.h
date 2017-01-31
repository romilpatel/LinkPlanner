# ifndef PROGRAM_INCLUDE_DECODER_H_
# define PROGRAM_INCLUDE_DECODER_H_

# include "netxpto.h"

# include <vector>

// Implements a IQ Decoder.
class Decoder : public Block {

	/* Input Parameters */

	t_integer m{ 4 };
<<<<<<< HEAD
	vector<t_complex> iqValues{ { 1.0, 1.0 },{ -1.0, 1.0 },{ -1.0, -1.0 },{ 1.0, -1.0 } };

=======
	vector<t_iqValues> iqAmplitudes{ {1.0, 1.0}, {-1.0, 1.0}, {1.0, -1.0}, {-1.0, -1.0} };
>>>>>>> f2dc156e00a385b8d7748985a96b912d02fc1056

	/* State Variables */

	bool firstTime{ true };

public:

	/* Methods */
	Decoder() {};
	Decoder(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig) {};

	void initialize(void);
	bool runBlock(void);

	void setM(int mValue);
	int getM() { return m; };

	void setIqAmplitudes(vector<t_iqValues> iqAmplitudesValues);
	vector<t_iqValues> getIqAmplitudes() { return iqAmplitudes; }

	/*void setIqValues(vector<t_complex> iq) { iqValues = iq; };
	vector<t_complex> getIqValues() { return iqValues; }*/

};

# endif
