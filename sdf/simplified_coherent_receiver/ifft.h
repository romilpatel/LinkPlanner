#pragma once
# ifndef PROGRAM_INCLUDE_IFFT_H_
# define PROGRAM_INCLUDE_IFFT_H_

# include "netxpto.h"


// Creates a complex signal from two real signals
class ifft : public Block
{
	/* State Variables */
	bool firstTime{ true };

public:

	/* Methods */
	ifft() {};
	ifft(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) : Block(InputSig, OutputSig) {};
	void initialize(void);
	bool runBlock(void);

};

# endif // PROGRAM_INCLUDE_REAL_TO_COMPLEX_H_



///////////////////////////////// from available code, new class Fft has been defined_Update according to simulator	//////////////////////////////////////


class Ifft
{

public:
	//vector<complex <double>> directTransformInReal(vector<double> real);

	//vector<double> inverseTransformInCP(vector<complex <double>> &In);

	void directTransform(vector<double> &real, vector<double> &imag);

	void inverseTransform(vector<double> &real, vector<double> &imag);
	
	void transformRadix2(vector<double> &real, vector<double> &imag);

	void transformBluestein(vector<double> &real, vector<double> &imag);

	//void convolve(const vector<double> &x, const vector<double> &y, vector<double> &out);

	void convolve(const vector<double> &xreal, const vector<double> &ximag, const vector<double> &yreal, const vector<double> &yimag, vector<double> &outreal, vector<double> &outimag);


};
