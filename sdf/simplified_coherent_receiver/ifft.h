#pragma once
# ifndef PROGRAM_INCLUDE_IFFT_H_
# define PROGRAM_INCLUDE_IFFT_H_

# include "netxpto.h"


#ifndef M_PI
#define M_PI  3.14159265358979323846
#endif


class Ifft
{

public:

	vector<double> ifft(std::vector<complex <double>> &In)
	{
		ComplexMult CMult;
		vector<double> re(In.size(), 0);
		vector<double> im(In.size(), 0);
		CMult.ComplexVect2ReImVect(In, re, im);
		directTransform(im, re);
		for (int x = 0; x != re.size(); ++x)
		{
			re[x] = re[x] / re.size();
			im[x] = im[x] / re.size();
		}

		vector<double> v_out(re.size(), 0);
		v_out = re;
		//CMult.ReImVect2ComplexVect(real, imag, v_out);

		return v_out;
	}


	void directTransform(vector<double> &real, vector<double> &imag);
	void inverseTransform(std::vector<double> &real, std::vector<double> &imag);
	void transformRadix2(vector<double> &real, vector<double> &imag);
	void transformBluestein(vector<double> &real, vector<double> &imag);
	void convolve(const vector<double> &xreal, const vector<double> &ximag, const vector<double> &yreal, const vector<double> &yimag, vector<double> &outreal, vector<double> &outimag);
		
};

#endif