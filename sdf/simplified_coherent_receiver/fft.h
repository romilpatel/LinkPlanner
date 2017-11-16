#pragma once

# ifndef PROGRAM_INCLUDE_FFT_H_
# define PROGRAM_INCLUDE_FFT_H_

# include "netxpto.h"
# ifndef M_PI
# define M_PI  3.14159265358979323846
# endif


class Fft
{

public:
	
	vector<complex <double>> fft(vector<double> &Input)
	{
		vector<double> im(Input.size(),0);						// Create a vector of length of input signal size :: initialize with 0
		vector<complex <double>> v_out(Input.size(), 0);		// Create a complex vector of length of input signal size :: initialize with 0 (for output)
		size_t n = Input.size();								// Size of vector

		if (n == 0)
			return v_out;
		else if ((n & (n - 1)) == 0)							// Is power of 2
			transformRadix2(Input, im);
		else													// More complicated algorithm for arbitrary sizes
			transformBluestein(Input, im);

		ComplexMult CMult;
		CMult.ReImVect2ComplexVect(Input, im, v_out);
		return v_out;
	}

void directTransform(vector<double> &real, vector<double> &imag);
void inverseTransform(vector<double> &real, vector<double> &imag);
void transformRadix2(vector<double> &real, vector<double> &imag);
void transformBluestein(vector<double> &real, vector<double> &imag);
void convolve(const vector<double> &xreal, const vector<double> &ximag, const vector<double> &yreal, const vector<double> &yimag, vector<double> &outreal, vector<double> &outimag);
};


#endif