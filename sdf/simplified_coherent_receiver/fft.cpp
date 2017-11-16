#include "netxpto.h"
#include "fft.h"

using namespace std;

void Fft::directTransform(vector<double> &real, vector<double> &imag)
{
	if (real.size() != imag.size())						// Length of real and imaginary part should be the same
		throw "Mismatched lengths";

	size_t n = real.size();
	if (n == 0)
		return;
	else if ((n & (n - 1)) == 0)						// Is power of 2
		transformRadix2(real, imag);
	else											    // More complicated algorithm for arbitrary sizes
		transformBluestein(real, imag);
};



void Fft:: transformRadix2(vector<double> &real, vector<double> &imag)
{
	if (real.size() != imag.size())						// Compute levels = floor(log2(n))
		throw "Mismatched lengths";
	size_t n = real.size();
	unsigned int levels;
	size_t temp = n;
	levels = 0;

	while (temp > 1)
	{
		levels++;
		temp >>= 1;
	}

	if (1u << levels != n)
		throw "Length is not a power of 2";
	

	vector<double> cosTable(n / 2);					// Trignometric tables
	vector<double> sinTable(n / 2);
	for (size_t i = 0; i < n / 2; i++)
	{
		cosTable[i] = cos(2 * M_PI * i / n);
		sinTable[i] = sin(2 * M_PI * i / n);
	}


	for (size_t i = 0; i < n; i++)					// Bit-reversed addressing permutation
	{
		size_t j = reverseBits(i, levels);
		if (j > i)
		{
			double temp = real[i];
			real[i] = real[j];
			real[j] = temp;
			temp = imag[i];
			imag[i] = imag[j];
			imag[j] = temp;
		}
	}


	for (size_t size = 2; size <= n; size *= 2)		// Cooley-Tukey decimation-in-time radix-2 FFT
	{
		size_t halfsize = size / 2;
		size_t tablestep = n / size;
		for (size_t i = 0; i < n; i += size)
		{
			for (size_t j = i, k = 0; j < i + halfsize; j++, k += tablestep)
			{
				double tpre = real[j + halfsize] * cosTable[k] + imag[j + halfsize] * sinTable[k];
				double tpim = -real[j + halfsize] * sinTable[k] + imag[j + halfsize] * cosTable[k];
				real[j + halfsize] = real[j] - tpre;
				imag[j + halfsize] = imag[j] - tpim;
				real[j] += tpre;
				imag[j] += tpim;
			}
		}
		if (size == n)								// Prevent overflow in 'size *= 2'

			break;
	}
};


////////// Subfunction for Radix-2 algorithim  //////////
/////////////////////////////////////////////////////////

static size_t reverseBits(size_t x, unsigned int n)
{
	size_t result = 0;
	unsigned int i;
	for (i = 0; i < n; i++, x >>= 1)
		result = (result << 1) | (x & 1);
	return result;
}

////////////////////////////////////////////
//////////// Bluestein Algorithim //////////
////////////////////////////////////////////

void Fft:: transformBluestein(vector<double> &real, vector<double> &imag)
{
	if (real.size() != imag.size())									// Find a power-of-2 convolution length m such that m >= n * 2 + 1
		throw "Mismatched lengths";

	size_t n = real.size();
	size_t m;
	size_t target;

	if (n > (SIZE_MAX - 1) / 2)
		throw "Vector too large";

	target = n * 2 + 1;

	for (m = 1; m < target; m *= 2)
	{
		if (SIZE_MAX / 2 < m)
			throw "Vector too large";
	}


	vector<double> cosTable(n), sinTable(n);							// Trignometric tables
	for (size_t i = 0; i < n; i++)
	{
		double temp = M_PI * (size_t)((unsigned long long)i * i % ((unsigned long long)n * 2)) / n;

		cosTable[i] = cos(temp);										// Less accurate version if long long is unavailable: double temp = M_PI * i * i / n;
		sinTable[i] = sin(temp);
	}


	vector<double> areal(m), aimag(m);									// Temporary vectors and preprocessing
	for (size_t i = 0; i < n; i++)
	{
		areal[i] = real[i] * cosTable[i] + imag[i] * sinTable[i];
		aimag[i] = -real[i] * sinTable[i] + imag[i] * cosTable[i];
	}
	vector<double> breal(m), bimag(m);
	breal[0] = cosTable[0];
	bimag[0] = sinTable[0];
	for (size_t i = 1; i < n; i++)
	{
		breal[i] = breal[m - i] = cosTable[i];
		bimag[i] = bimag[m - i] = sinTable[i];
	}


	vector<double> creal(m), cimag(m);									// Convolution
	convolve(areal, aimag, breal, bimag, creal, cimag);

	// Postprocessing
	for (size_t i = 0; i < n; i++) {
		real[i] = creal[i] * cosTable[i] + cimag[i] * sinTable[i];
		imag[i] = -creal[i] * sinTable[i] + cimag[i] * cosTable[i];
	}
};


////////// Subfunction for Bluestein algorithim  //////////
///////////////////////////////////////////////////////////
void Fft:: convolve(const vector<double> &xreal, const vector<double> &ximag, const vector<double> &yreal, const vector<double> &yimag, vector<double> &outreal, vector<double> &outimag)
{
	if (xreal.size() != ximag.size() || xreal.size() != yreal.size() || yreal.size() != yimag.size() || xreal.size() != outreal.size() || outreal.size() != outimag.size())
		throw "Mismatched lengths";

	size_t n = xreal.size();
	vector<double> xr(xreal);
	vector<double> xi(ximag);
	vector<double> yr(yreal);
	vector<double> yi(yimag);

	directTransform(xr, xi);
	directTransform(yr, yi);
	for (size_t i = 0; i < n; i++) {
		double temp = xr[i] * yr[i] - xi[i] * yi[i];
		xi[i] = xi[i] * yr[i] + xr[i] * yi[i];
		xr[i] = temp;
	}

	inverseTransform(xr, xi);
	for (size_t i = 0; i < n; i++)		// Scaling (because this FFT implementation omits it)
	{
		outreal[i] = xr[i] / n;
		outimag[i] = xi[i] / n;
	}
};


void Fft :: inverseTransform(vector<double> &real, vector<double> &imag)
{
	directTransform(imag, real);
	for (int x = 0; x != real.size(); ++x)
	{
		real[x] = real[x] / real.size();
		imag[x] = imag[x] / real.size();
	}
};
