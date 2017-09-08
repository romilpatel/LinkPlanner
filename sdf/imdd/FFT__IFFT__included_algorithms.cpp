//=================================================================================================
//============================FFT (Fast Fourier Transform):========================================
//=================================================================================================


//=================================================================================================
//====================1º algorithm (associated to 1º IFFT algorithm):==============================
//=================================================================================================

#include <complex>
#include <iostream>
#include <valarray>
const double PI = 3.141592653589793238460;
typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray; 
// Cooley-Tukey FFT (in-place, divide-and-conquer)
void fft(CArray& x)
{
    const size_t N = x.size();
    if (N <= 1) return;
    // divide
    CArray even = x[std::slice(0, N/2, 2)];
    CArray  odd = x[std::slice(1, N/2, 2)];
    // conquer
    fft(even);
    fft(odd);
    // combine
    for (size_t k = 0; k < N/2; ++k)
    {
        Complex t = std::polar(1.0, -2 * PI * k / N) * odd[k];
        x[k    ] = even[k] + t;
        x[k+N/2] = even[k] - t;
    }
}
//=================================================================================================
//====================2º algorithm (associated to 1º IFFT algorithm):==============================
//=================================================================================================

// Cooley-Tukey FFT (in-place, breadth-first, decimation-in-frequency)
#include <complex>
#include <iostream>
#include <valarray>
typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray; 
void fft(CArray &x)
{
	// DFT
	unsigned int N = x.size(), k = N, n;
	double thetaT = 3.14159265358979323846264338328L / N;
	Complex phiT = Complex(cos(thetaT), sin(thetaT)), T;
	while (k > 1)
	{
		n = k;
		k >>= 1;
		phiT = phiT * phiT;
		T = 1.0L;
		for (unsigned int l = 0; l < k; l++)
		{
			for (unsigned int a = l; a < N; a += n)
			{
				unsigned int b = a + k;
				Complex t = x[a] - x[b];
				x[a] += x[b];
				x[b] = t * T;
			}
			T *= phiT;
		}
	}
	// Decimate
	unsigned int m = (unsigned int)log2(N);
	for (unsigned int a = 0; a < N; a++)
	{
		unsigned int b = a;
		// Reverse bits
		b = (((b & 0xaaaaaaaa) >> 1) | ((b & 0x55555555) << 1));
		b = (((b & 0xcccccccc) >> 2) | ((b & 0x33333333) << 2));
		b = (((b & 0xf0f0f0f0) >> 4) | ((b & 0x0f0f0f0f) << 4));
		b = (((b & 0xff00ff00) >> 8) | ((b & 0x00ff00ff) << 8));
		b = ((b >> 16) | (b << 16)) >> (32 - m);
		if (b > a)
		{
			Complex t = x[a];
			x[a] = x[b];
			x[b] = t;
		}
	}
}
//=================================================================================================
//====================3º algorithm (included FFT and IFFT):========================================
//=================================================================================================

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#define q	3		/* for 2^3 points */
#define N	(1<<q)		/* N-point FFT, iFFT */
typedef float real;
typedef struct{real Re; real Im;} complex;
#ifndef PI
# define PI	3.14159265358979323846264338327950288
#endif
/* Print a vector of complexes as ordered pairs. */
static void
print_vector(
	     const char *title,
	     complex *x,
	     int n)
{
  int i;
  printf("%s (dim=%d):", title, n);
  for(i=0; i<n; i++ ) printf(" %5.2f,%5.2f ", x[i].Re,x[i].Im);
  putchar('\n');
  return;
}
/* 
   fft(v,N):
   [0] If N==1 then return.
   [1] For k = 0 to N/2-1, let ve[k] = v[2*k]
   [2] Compute fft(ve, N/2);
   [3] For k = 0 to N/2-1, let vo[k] = v[2*k+1]
   [4] Compute fft(vo, N/2);
   [5] For m = 0 to N/2-1, do [6] through [9]
   [6]   Let w.re = cos(2*PI*m/N)
   [7]   Let w.im = -sin(2*PI*m/N)
   [8]   Let v[m] = ve[m] + w*vo[m]
   [9]   Let v[m+N/2] = ve[m] - w*vo[m]
 */
void
fft( complex *v, int n, complex *tmp )
{
  if(n>1) {			/* otherwise, do nothing and return */
    int k,m;    complex z, w, *vo, *ve;
    ve = tmp; vo = tmp+n/2;
    for(k=0; k<n/2; k++) {
      ve[k] = v[2*k];
      vo[k] = v[2*k+1];
    }
    fft( ve, n/2, v );		/* FFT on even-indexed elements of v[] */
    fft( vo, n/2, v );		/* FFT on odd-indexed elements of v[] */
    for(m=0; m<n/2; m++) {
      w.Re = cos(2*PI*m/(double)n);
      w.Im = -sin(2*PI*m/(double)n);
      z.Re = w.Re*vo[m].Re - w.Im*vo[m].Im;	/* Re(w*vo[m]) */
      z.Im = w.Re*vo[m].Im + w.Im*vo[m].Re;	/* Im(w*vo[m]) */
      v[  m  ].Re = ve[m].Re + z.Re;
      v[  m  ].Im = ve[m].Im + z.Im;
      v[m+n/2].Re = ve[m].Re - z.Re;
      v[m+n/2].Im = ve[m].Im - z.Im;
    }
  }
  return;
}
/* 
   ifft(v,N):
   [0] If N==1 then return.
   [1] For k = 0 to N/2-1, let ve[k] = v[2*k]
   [2] Compute ifft(ve, N/2);
   [3] For k = 0 to N/2-1, let vo[k] = v[2*k+1]
   [4] Compute ifft(vo, N/2);
   [5] For m = 0 to N/2-1, do [6] through [9]
   [6]   Let w.re = cos(2*PI*m/N)
   [7]   Let w.im = sin(2*PI*m/N)
   [8]   Let v[m] = ve[m] + w*vo[m]
   [9]   Let v[m+N/2] = ve[m] - w*vo[m]
 */
void
ifft( complex *v, int n, complex *tmp )
{
  if(n>1) {			/* otherwise, do nothing and return */
    int k,m;    complex z, w, *vo, *ve;
    ve = tmp; vo = tmp+n/2;
    for(k=0; k<n/2; k++) {
      ve[k] = v[2*k];
      vo[k] = v[2*k+1];
    }
    ifft( ve, n/2, v );		/* FFT on even-indexed elements of v[] */
    ifft( vo, n/2, v );		/* FFT on odd-indexed elements of v[] */
    for(m=0; m<n/2; m++) {
      w.Re = cos(2*PI*m/(double)n);
      w.Im = sin(2*PI*m/(double)n);
      z.Re = w.Re*vo[m].Re - w.Im*vo[m].Im;	/* Re(w*vo[m]) */
      z.Im = w.Re*vo[m].Im + w.Im*vo[m].Re;	/* Im(w*vo[m]) */
      v[  m  ].Re = ve[m].Re + z.Re;
      v[  m  ].Im = ve[m].Im + z.Im;
      v[m+n/2].Re = ve[m].Re - z.Re;
      v[m+n/2].Im = ve[m].Im - z.Im;
    }
  }
  return;
}
int
main(void)
{
  complex v[N], v1[N], scratch[N];
  int k;
  /* Fill v[] with a function of known FFT: */
  for(k=0; k<N; k++) {
    v[k].Re = 0.125*cos(2*PI*k/(double)N);
    v[k].Im = 0.125*sin(2*PI*k/(double)N);
    v1[k].Re =  0.3*cos(2*PI*k/(double)N);
    v1[k].Im = -0.3*sin(2*PI*k/(double)N);
  }  
  /* FFT, iFFT of v[]: */
  print_vector("Orig", v, N);
  fft( v, N, scratch );
  print_vector(" FFT", v, N);
  ifft( v, N, scratch );
  print_vector("iFFT", v, N);
  /* FFT, iFFT of v1[]: */
  print_vector("Orig", v1, N);
  fft( v1, N, scratch );
  print_vector(" FFT", v1, N);
  ifft( v1, N, scratch );
  print_vector("iFFT", v1, N);
  exit(EXIT_SUCCESS);
}
//=================================================================================================
//====================4º algorithm:================================================================
//=================================================================================================

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
using namespace std;
void fft_recur(long, double* r, double* i);
int main (int nNumberofArgs, char* pszArgs[ ] ) { // arguments needed for Dev C++ I/O
const long N = 1024;   double sample_rate = 44100., r[N] = {0.}, i[N] = {0.}, w[N] = {0.} ;
long n;      double  t, twopi = 2*3.141592653589793238;
double amp_sq[N], F, fbin, amp, power, c = 2.3;
for (n = 0; n < N; n++)  {  // generate test data
    t = twopi*n/sample_rate;
    r[n] = 1.*cos(16351.*t)+1.*cos(16996.*t)+1.*cos(17211.*t)+1.*cos(17426.*t) ;
} // end for
//Gaussian window as computed in [MCEACH94] program
double z;
for (n = 0; n < N/2; n++) {
    z = (.5+(N/2)-1.-n)*(twopi/2.)/N;
    w[n] = exp(-c*z*z);
    w[N-1-n] = w[n];
}
//multiply input data by window points
for (n = 0; n < N; n++)  {
    r[n] = w[n]*r[n];    // we're overwriting r[n] with the windowed r[n]
} //end for
fft_recur(N, r, i);       // note: fft is not scaled
// compute amplitude squared
for (n = 0; n < N/2+1; n++)  {
    amp_sq[n] = r[n]*r[n]+i[n]*i[n];
} //end for
// compute natural log of FFT outputs
for (n = 0; n < N/2+1; n++)  {
    r[n] = .5*log( amp_sq[n] ) ; // r[n] is now the natural log of the amplitude of FFT bin 'n'
} // end for                     // .5*log(A squared) = log(A)
cout<<"\n\nfrequency and amplitude estimation results\n\n n        magnitude      frequency       amplitude\n\n";
for (n = 370; n < 415; n++)  {
    fbin = n+.5+.5*c*(r[n+1]-r[n]);   // r[n+1] and r[n] are ln(b) and ln(a)
    F = (sample_rate/N)*fbin;
    amp = sqrt(c)*exp(r[n]+((fbin-n)*(fbin-n))/c)*(2.0*sqrt(twopi/2.)/N) ;
    printf("%2d\t%9.5f\t%9.5f\t%9.5f\n",n,amp_sq[n],F,amp);
} //end for
system ("PAUSE");
return 0;
} // end main
//******************** fft_recur ***********************
void fft_recur(long N, double *r, double *i)  {
long h, i1, j = 0, k, i2 = N/2, l1, l2 = 1;
double c = -1.0, s = 0.0, t1, t2, u1, u2;

for (h = 0; h < N-2; h++) {    // ***** bit reverse starts here ***
    if (h < j) {
       t1 = r[h]; r[h] = r[j]; r[j] = t1; 
       t2 = i[h]; i[h] = i[j]; i[j] = t2;
    }
    k = i2;
    while (k <= j) {
          j = j - k;      k = k/2;
    }
    j = j + k;
}   //****** bit reverse done ******
for (k = 1; k < N; k = k*2) {
    l1 = l2;     l2 = l2*2;
    u1 = 1.0;    u2 = 0.0;
    for (j = 0; j < l1; j++) {
        for (h = j; h < N; h = h + l2) {
            i1 = h + l1;
            t2 = (r[i1] - i[i1])*u2 ;
            t1 = t2 + r[i1]*(u1 - u2) ;
            t2 = t2 + i[i1]*(u1 + u2) ;
            r[i1] = r[h] - t1;
            i[i1] = i[h] - t2;
            r[h]  = r[h] + t1;
            i[h]  = i[h] + t2;              
        } // end for over h
        t1 = u1 * c - u2 * s;
        u2 = u1 * s + u2 * c;
        u1 = t1;  //x = u1 - u2;    y = u1 + u2;
    } // end for over j
    s = - sqrt((1.0 - c) / 2.0);
    c =   sqrt((1.0 + c) / 2.0);
} // end for over k
} // end fft
//=================================================================================================
//====================5º algorithm:================================================================
//=================================================================================================

#include "FFT.h"
#include "Complex.h"
void FFT::del_all() {
  delete input_data;
  delete bitrev_data;
}
bool FFT::test_pwr2(unsigned int n)
{
  if( n < 2 || (n & (n-1)) ) return false;
  return true;
}
// reverse bits in provided index

int FFT::rev_bits(unsigned int index,int size)
{
  int rev = 0;
  for(;size > 1; size>>=1)
  {
    rev = (rev << 1) | (index & 1);
    index >>= 1;
  }
  return rev;
}
FFT::FFT(int n) {
  size = 0;
  input_data = NULL;
  bitrev_data = NULL;
  initialize(n);
}
FFT::~FFT() {
  del_all();
}
void FFT::initialize(unsigned int n, bool del) {
  if(!test_pwr2(n)) {
    valid = false;
    fprintf(stderr,"Error: array size is not a power of 2\n");
  }
  else {
    valid = true;
    if(size != n) {
      size = n;
      pi2 = M_PI * 2.0;
      scale = 1.0/size;
      if(del) {
        del_all();
      }
      input_data  = new Complex[n];
      bitrev_data = new Complex*[n];
      // preload array of bit-reversed
      // pointers to input data
      int rb;
      for(unsigned int i = 0;i < n;i++) {
        rb = rev_bits(i,n);
        bitrev_data[rb] = &input_data[i];
      }
    }
  }
}
void FFT::resize(int n) {
  initialize(n,true);
}
Complex* FFT::array_input() {
  return input_data;
}
Complex** FFT::array_output() {
  return bitrev_data;
}
void FFT::fft1(bool inverse)
{
  if(valid) {
    unsigned long imax,istep,m,i,j;
    // these variables are used to maintain trig arguments by iteration,
    // so they should always be doubles to avoid erosion of accuracy
    double wtemp,wr,wpr,wpi,wi,theta;
    Complex tc;
    // Danielson-Lanzcos routine
    imax = 1;
    istep = 2;
    DATATYPE ps = (inverse)?-pi2:pi2;
    while (imax < size)
    {
      istep = imax << 1;
      theta= ps/istep;
      wtemp=sin(0.5*theta);
      wpr = -2.0*wtemp*wtemp;
      wpi = sin(theta);
      wr = 1.0;
      wi = 0.0;
      for (m=0; m<imax; ++m) {
        for (i=m; i<size; i+=istep) {
          j = i+imax;
          tc.re = wr * bitrev_data[j]->re - wi * bitrev_data[j]->im;
          tc.im = wr * bitrev_data[j]->im + wi * bitrev_data[j]->re;
          *bitrev_data[j] = *bitrev_data[i] - tc;
          *bitrev_data[i] += tc;
        }
        wr=(wtemp=wr)*wpr-wi*wpi+wr;
        wi=wi*wpr+wtemp*wpi+wi;
      }
      imax = istep;
    } 
    if(!inverse) {
      for(unsigned int i = 0;i < size;i++) {
        *bitrev_data[i] *= scale;
      }
    }
  }
}
//=================================================================================================
//====================6º algorithm (included FFT and IFFT):========================================
//=================================================================================================

//   Include declaration file
#include "fft.h"
//   Include math library
#include <math.h>
//   FORWARD FOURIER TRANSFORM
//     Input  - input data
//     Output - transform result
//     N      - length of both input data and result
bool CFFT::Forward(const complex *const Input, complex *const Output, const unsigned int N)
{
	//   Check input parameters
	if (!Input || !Output || N < 1 || N & (N - 1))
		return false;
	//   Initialize data
	Rearrange(Input, Output, N);
	//   Call FFT implementation
	Perform(Output, N);
	//   Succeeded
	return true;
}
//   FORWARD FOURIER TRANSFORM, INPLACE VERSION
//     Data - both input data and output
//     N    - length of input data
bool CFFT::Forward(complex *const Data, const unsigned int N)
{
	//   Check input parameters
	if (!Data || N < 1 || N & (N - 1))
		return false;
	//   Rearrange
	Rearrange(Data, N);
	//   Call FFT implementation
	Perform(Data, N);
	//   Succeeded
	return true;
}
//   INVERSE FOURIER TRANSFORM
//     Input  - input data
//     Output - transform result
//     N      - length of both input data and result
//     Scale  - if to scale result
bool CFFT::Inverse(const complex *const Input, complex *const Output, const unsigned int N, const bool Scale /* = true */)
{
	//   Check input parameters
	if (!Input || !Output || N < 1 || N & (N - 1))
		return false;
	//   Initialize data
	Rearrange(Input, Output, N);
	//   Call FFT implementation
	Perform(Output, N, true);
	//   Scale if necessary
	if (Scale)
		CFFT::Scale(Output, N);
	//   Succeeded
	return true;
}
//   INVERSE FOURIER TRANSFORM, INPLACE VERSION
//     Data  - both input data and output
//     N     - length of both input data and result
//     Scale - if to scale result
bool CFFT::Inverse(complex *const Data, const unsigned int N, const bool Scale /* = true */)
{
	//   Check input parameters
	if (!Data || N < 1 || N & (N - 1))
		return false;
	//   Rearrange
	Rearrange(Data, N);
	//   Call FFT implementation
	Perform(Data, N, true);
	//   Scale if necessary
	if (Scale)
		CFFT::Scale(Data, N);
	//   Succeeded
	return true;
}
//   Rearrange function
void CFFT::Rearrange(const complex *const Input, complex *const Output, const unsigned int N)
{
	//   Data entry position
	unsigned int Target = 0;
	//   Process all positions of input signal
	for (unsigned int Position = 0; Position < N; ++Position)
	{
		//  Set data entry
		Output[Target] = Input[Position];
		//   Bit mask
		unsigned int Mask = N;
		//   While bit is set
		while (Target & (Mask >>= 1))
			//   Drop bit
			Target &= ~Mask;
		//   The current bit is 0 - set it
		Target |= Mask;
	}
}
//   Inplace version of rearrange function
void CFFT::Rearrange(complex *const Data, const unsigned int N)
{
	//   Swap position
	unsigned int Target = 0;
	//   Process all positions of input signal
	for (unsigned int Position = 0; Position < N; ++Position)
	{
		//   Only for not yet swapped entries
		if (Target > Position)
		{
			//   Swap entries
			const complex Temp(Data[Target]);
			Data[Target] = Data[Position];
			Data[Position] = Temp;
		}
		//   Bit mask
		unsigned int Mask = N;
		//   While bit is set
		while (Target & (Mask >>= 1))
			//   Drop bit
			Target &= ~Mask;
		//   The current bit is 0 - set it
		Target |= Mask;
	}
}
//   FFT implementation
void CFFT::Perform(complex *const Data, const unsigned int N, const bool Inverse /* = false */)
{
	const double pi = Inverse ? 3.14159265358979323846 : -3.14159265358979323846;
	//   Iteration through dyads, quadruples, octads and so on...
	for (unsigned int Step = 1; Step < N; Step <<= 1)
	{
		//   Jump to the next entry of the same transform factor
		const unsigned int Jump = Step << 1;
		//   Angle increment
		const double delta = pi / double(Step);
		//   Auxiliary sin(delta / 2)
		const double Sine = sin(delta * .5);
		//   Multiplier for trigonometric recurrence
		const complex Multiplier(-2. * Sine * Sine, sin(delta));
		//   Start value for transform factor, fi = 0
		complex Factor(1.);
		//   Iteration through groups of different transform factor
		for (unsigned int Group = 0; Group < Step; ++Group)
		{
			//   Iteration within group 
			for (unsigned int Pair = Group; Pair < N; Pair += Jump)
			{
				//   Match position
				const unsigned int Match = Pair + Step;
				//   Second term of two-point transform
				const complex Product(Factor * Data[Match]);
				//   Transform for fi + pi
				Data[Match] = Data[Pair] - Product;
				//   Transform for fi
				Data[Pair] += Product;
			}
			//   Successive transform factor via trigonometric recurrence
			Factor = Multiplier * Factor + Factor;
		}
	}
}
//   Scaling of inverse FFT result
void CFFT::Scale(complex *const Data, const unsigned int N)
{
	const double Factor = 1. / double(N);
	//   Scale all data entries
	for (unsigned int Position = 0; Position < N; ++Position)
		Data[Position] *= Factor;
}
//=================================================================================================
//====================7º algorithm (included FFT and IFFT):========================================
//=================================================================================================

#include "dft.h"
#include <math.h>
#include <complex>
#include <algorithm>
#include <stack>
using namespace std;
/*
 * "Butterfly" transform.
 */
inline void butterfly(comp &x, comp &y, comp w)
{
   comp p = x, q = y*w;
   x = p + q;
   y = p - q;
}
/*
 * Series of butterfly transforms required by the FFT algorithm.
 */
inline void mass_butterfly(comp *array, int size, comp w)
{
   comp power(1.0, 0.0);
   int n = size/2;
   
   for(int i = 0; i < n; i++) {
      butterfly(array[i], array[i+n], power);
      power *= w;
   }
}
/*
 * Given a number ``x'' returns the number which has the same bits as ``x'',
 * but in the reverse order
 */
inline unsigned int backwards(unsigned int x, int length)
{
   unsigned int result = 0;
   unsigned int bit = 1u;
   unsigned int reverse = 1u<<(length-1);
   for(int i = 0; i < length && x != 0; i++) {
      if(x & bit) {
         result |= reverse;
         x &= ~bit;
      }
      bit <<= 1;
      reverse >>= 1;
   }
   return result;
}
/*
 * Moves elements of the array as required by the iterative FFT implementation.
 * ``size'' must be a power of 2.
 */
static void reposition(comp *array, int size)
{
   // Determine the bit length
   int length = 0;
   while(1u << length < (unsigned int)size)
      length++;
   // Swap elements at positions k and reverse(k)
   for(int i = 0; i < size; i++) {
      int j = backwards(i, length);
      if(i <= j)
         swap(array[i], array[j]);
   }
}
/*
 * Does the Discrete Fourier Transform.  Takes time O(size * log(size)).
 * ``size'' must be a power of 2.
 */
void fourier_transform(comp *array, int size)
{
   // Arrange numbers in a convenient order
   reposition(array, size);

   // Prepare roots of unity for every step
   int step;
   comp root = exp(comp(0.0, 2.0*M_PI/size));
   stack<comp> roots;
   for(step=size; step != 1; step /= 2) {
      roots.push(root);
      root *= root;
   }
   // Do lots of butterfly transforms
   for(step = 2; step <= size; step *= 2) {
      root = roots.top();
      roots.pop();
      for(int i = 0; i < size; i += step)   
         mass_butterfly(array + i, step, root);
   }
}
/*
 * The inverse DFT.
 */
void inverse_fourier_transform(comp *array, int size)
{
   conjugate(array, size);
   fourier_transform(array, size);
   conjugate(array, size);
   for(int i = 0; i < size; i++)
      array[i] = array[i] / (double)size;
}
/*
 * Replaces every element of the vector by its complex conjugate.
 */
void conjugate(comp *array, int size)
{
   for(int i = 0; i < size; i++)
      array[i] = conj(array[i]);
}
/*
 * Multiplies two vectors element by element.
 */
void multiply(comp *arr1, comp *arr2, comp *result, int size)
{
   for(int i = 0; i < size; i++)
      result[i] = arr1[i] * arr2[i];
}
/*
 * Finds the convolution of two vectors (the product of two polynomials, given
 * that the result has power less than ``size'').  ``size'' must be a power of
 * 2.
 */
void convolution(comp *arr1, comp *arr2, comp *result, int size)
{
   fourier_transform(arr1, size);
   fourier_transform(arr2, size);
   multiply(arr1, arr2, result, size);
   inverse_fourier_transform(result, size);
}



//=================================================================================================
//====================IFFT (Inverse Fast Fourier Transform)::======================================
//=================================================================================================


//=================================================================================================
//====================1º algorithm (associated to 1º and 2º FFT algorithm)::=======================
//=================================================================================================

#include <complex>
#include <iostream>
#include <valarray>
typedef std::complex<double> Complex;
typedef std::valarray<Complex> CArray; 
// inverse fft (in-place)
void ifft(CArray& x)
{
    // conjugate the complex numbers
    x = x.apply(std::conj);
    // forward fft
    fft( x );
    // conjugate the complex numbers again
    x = x.apply(std::conj);
    // scale the numbers
    x /= x.size();
}
int main()
{
    const Complex test[] = { 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0 };
    CArray data(test, 8);
    // forward fft
    fft(data);
    std::cout << "fft" << std::endl;
    for (int i = 0; i < 8; ++i)
    {
        std::cout << data[i] << std::endl;
    }
    // inverse fft
    ifft(data);
    std::cout << std::endl << "ifft" << std::endl;
    for (int i = 0; i < 8; ++i)
    {
        std::cout << data[i] << std::endl;
    }
    return 0;
}


//=================================================================================================
//====================# included:==================================================================
//=================================================================================================

//=================================================================================================
//====================FFT.h (5º algorithm):========================================================
//=================================================================================================

#ifndef FFT_H
#define FFT_H
#include <cstdio>
#include <cmath>
// NOTE: for greater speed, set DATATYPE float
// for greater accuracy, set DATATYPE double
#define DATATYPE float
#include "Complex.h"
class FFT {
  unsigned int size;
  DATATYPE scale;
  Complex *input_data;
  Complex **bitrev_data;
  bool valid;
  void del_all();
  bool test_pwr2(unsigned int n);
  int rev_bits(unsigned int index,int size);
  void initialize(unsigned int n, bool del = false);
  public:
  DATATYPE pi2;
  FFT(int n);
  ~FFT();
  void resize(int n);
  Complex* array_input();
  Complex** array_output();
  void fft1(bool inverse = false);
};
#endif
//=================================================================================================
//====================DFT.cpp (5º algorithm):======================================================
//=================================================================================================

#include "DFT.h"
#include "Complex.h"
/*
 *
 * This source file and class exists only to show
 * the simplicity of the DFT. The DFT is very slow
 * and inefficient, its value lies only in clarifying
 * the Discrete Fourier Transform.
 *
 */
void DFT::del_all() {
  delete input_data;
  delete output_data;
}
DFT::DFT(int n) {
  size = 0;
  input_data = NULL;
  output_data = NULL;
  initialize(n);
}
DFT::~DFT() {
  del_all();
}
void DFT::initialize(unsigned int n, bool del) {
  if(size != n) {
    size = n;
    pi2 = M_PI * 2.0;
    scale = 1.0/size;
    if(del) {
      del_all();
    }
    input_data  = new Complex[n];
    output_data = new Complex[n];
  }
}
void DFT::resize(int n) {
  initialize(n,true);
}
Complex* DFT::array_input() {
  return input_data;
}
Complex* DFT::array_output() {
  return output_data;
}
void DFT::dft1(bool inverse)
{
  double pi2 = (inverse)?2.0 * M_PI:-2.0 * M_PI;
  double a,ca,sa;
  double invs = 1.0 / size;
  for(unsigned int y = 0;y < size;y++) {
    output_data[y] = 0;
    for(unsigned int x = 0;x < size;x++) {
      a = pi2 * y * x * invs;
      ca = cos(a);
      sa = sin(a);
      output_data[y].re += input_data[x].re * ca - input_data[x].im * sa;
      output_data[y].im += input_data[x].re * sa + input_data[x].im * ca;
    }
    if(!inverse) {
      output_data[y] *= invs;
    }
  }
}
//=================================================================================================
//====================DFT.h (5º algorithm):========================================================
//=================================================================================================

#ifndef FT_H
#define DFT_H
#include <cstdio>
#include <cmath>
// NOTE: for greater speed, set DATATYPE float
// for greater accuracy, set DATATYPE double
#define DATATYPE float
#include "Complex.h"
class DFT {
  unsigned int size;
  DATATYPE scale;
  Complex *input_data;
  Complex *output_data;
  void del_all();
  int rev_bits(unsigned int index,int size);
  void initialize(unsigned int n, bool del = false);
  public:
  DATATYPE pi2;
  DFT(int n);
  ~DFT();
  
  void resize(int n);
  Complex* array_input();
  Complex* array_output();
  void dft1(bool inverse = false);
};
#endif
//=================================================================================================
//====================Complex.h (5º algorithm):====================================================
//=================================================================================================

#ifndef COMPLEX_H
#define COMPLEX_H
#include <cmath>
// NOTE: change to DATATYPE double for more data resolution and accuracy
// but somewhat slower conversion speed
#define DATATYPE float
// a utility complex data class
class Complex {
  public:
  DATATYPE re;
  DATATYPE im;
  Complex();
  Complex(const Complex& v);
  Complex(const DATATYPE& re, const DATATYPE& im);
  void operator=(Complex v);
  void operator=(DATATYPE v);
  Complex operator-(Complex v);
  Complex operator*(DATATYPE v);
  Complex* operator+=(Complex v);
  Complex* operator-=(Complex v);
  void operator*=(Complex v);
  void operator*=(DATATYPE v);
  DATATYPE m();
  DATATYPE sumsq();
  DATATYPE a();
};
#endif
//=================================================================================================
//====================Complex.cpp (5º algorithm):==================================================
//=================================================================================================

// a utility complex data class
#include "Complex.h"
Complex::Complex() {
  re = 0;
  im = 0;
}
Complex::Complex(const Complex& v) {
  re = v.re;
  im = v.im;
}
Complex::Complex(const DATATYPE& re, const DATATYPE& im) {
  this->re = re;
  this->im = im;
}
void Complex::operator=(Complex v) {
  re = v.re;
  im = v.im;
}
void Complex::operator=(DATATYPE v) {
  re = v;
  im = v;
}
Complex Complex::operator-(Complex v) {
  return Complex(re-v.re,im-v.im);
}
Complex Complex::operator*(DATATYPE v) {
  return Complex(re*v,im*v);
}
Complex* Complex::operator+=(Complex v)
{
  re += v.re;
  im += v.im;
  return this;
}
Complex* Complex::operator-=(Complex v)
{
  re -= v.re;
  im -= v.im;
  return this;
}
void Complex::operator*=(Complex v)
{
  re *= v.re;
  im *= v.im;
}
void Complex::operator*=(DATATYPE v)
{
  re *= v;
  im *= v;
}
DATATYPE Complex::m() {
  return sqrt(re*re+im*im);
}
DATATYPE Complex::sumsq() {
  return re*re+im*im;
}
DATATYPE Complex::a() {
  DATATYPE a = atan2(re,im);
  if(a < 0) {
    a = (M_PI * 2) + a;
  }
  return a;
}
//=================================================================================================
//====================fft.h (6º algorithm):========================================================
//=================================================================================================

#ifndef _FFT_H_
#define _FFT_H_
//   Include complex numbers header
#include "complex.h"
class CFFT
{
public:
	//   FORWARD FOURIER TRANSFORM
	//     Input  - input data
	//     Output - transform result
	//     N      - length of both input data and result
	static bool Forward(const complex *const Input, complex *const Output, const unsigned int N);

	//   FORWARD FOURIER TRANSFORM, INPLACE VERSION
	//     Data - both input data and output
	//     N    - length of input data
	static bool Forward(complex *const Data, const unsigned int N);

	//   INVERSE FOURIER TRANSFORM
	//     Input  - input data
	//     Output - transform result
	//     N      - length of both input data and result
	//     Scale  - if to scale result
	static bool Inverse(const complex *const Input, complex *const Output, const unsigned int N, const bool Scale = true);
	//   INVERSE FOURIER TRANSFORM, INPLACE VERSION
	//     Data  - both input data and output
	//     N     - length of both input data and result
	//     Scale - if to scale result
	static bool Inverse(complex *const Data, const unsigned int N, const bool Scale = true);
protected:
	//   Rearrange function and its inplace version
	static void Rearrange(const complex *const Input, complex *const Output, const unsigned int N);
	static void Rearrange(complex *const Data, const unsigned int N);
	//   FFT implementation
	static void Perform(complex *const Data, const unsigned int N, const bool Inverse = false);
	//   Scaling of inverse FFT result
	static void Scale(complex *const Data, const unsigned int N);
};
#endif
//=================================================================================================
//====================complex.h (6º algorithm):====================================================
//=================================================================================================
#ifndef _COMPLEX_H_
#define _COMPLEX_H_
class complex
{
protected:
	//   Internal presentation - real and imaginary parts
	double m_re;
	double m_im;
public:
	//   Imaginary unity
	static const complex i;
	static const complex j;
	//   Constructors
	complex(): m_re(0.), m_im(0.) {}
	complex(double re, double im): m_re(re), m_im(im) {}
	complex(double val): m_re(val), m_im(0.) {}
	//   Assignment
	complex& operator= (const double val)
	{
		m_re = val;
		m_im = 0.;
		return *this;
	}
	//   Basic operations - taking parts
	double re() const { return m_re; }
	double im() const { return m_im; }

	//   Conjugate number
	complex conjugate() const
	{
		return complex(m_re, -m_im);
	}
	//   Norm   
	double norm() const
	{
		return m_re * m_re + m_im * m_im;
	}
	//   Arithmetic operations
	complex operator+ (const complex& other) const
	{
		return complex(m_re + other.m_re, m_im + other.m_im);
	}
	complex operator- (const complex& other) const
	{
		return complex(m_re - other.m_re, m_im - other.m_im);
	}
	complex operator* (const complex& other) const
	{
		return complex(m_re * other.m_re - m_im * other.m_im,
			m_re * other.m_im + m_im * other.m_re);
	}
	complex operator/ (const complex& other) const
	{
		const double denominator = other.m_re * other.m_re + other.m_im * other.m_im;
		return complex((m_re * other.m_re + m_im * other.m_im) / denominator,
			(m_im * other.m_re - m_re * other.m_im) / denominator);
	}
	complex& operator+= (const complex& other)
	{
		m_re += other.m_re;
		m_im += other.m_im;
		return *this;
	}
	complex& operator-= (const complex& other)
	{
		m_re -= other.m_re;
		m_im -= other.m_im;
		return *this;
	}
	complex& operator*= (const complex& other)
	{
		const double temp = m_re;
		m_re = m_re * other.m_re - m_im * other.m_im;
		m_im = m_im * other.m_re + temp * other.m_im;
		return *this;
	}
	complex& operator/= (const complex& other)
	{
		const double denominator = other.m_re * other.m_re + other.m_im * other.m_im;
		const double temp = m_re;
		m_re = (m_re * other.m_re + m_im * other.m_im) / denominator;
		m_im = (m_im * other.m_re - temp * other.m_im) / denominator;
		return *this;
	}
	complex& operator++ ()
	{
		++m_re;
		return *this;
	}
	complex operator++ (int)
	{
		complex temp(*this);
		++m_re;
		return temp;
	}
	complex& operator-- ()
	{
		--m_re;
		return *this;
	}
	complex operator-- (int)
	{
		complex temp(*this);
		--m_re;
		return temp;
	}
	complex operator+ (const double val) const
	{
		return complex(m_re + val, m_im);
	}
	complex operator- (const double val) const
	{
		return complex(m_re - val, m_im);
	}

	complex operator* (const double val) const
	{
		return complex(m_re * val, m_im * val);
	}
	complex operator/ (const double val) const
	{
		return complex(m_re / val, m_im / val);
	}

	complex& operator+= (const double val)
	{
		m_re += val;
		return *this;
	}
	complex& operator-= (const double val)
	{
		m_re -= val;
		return *this;
	}
	complex& operator*= (const double val)
	{
		m_re *= val;
		m_im *= val;
		return *this;
	}
	complex& operator/= (const double val)
	{
		m_re /= val;
		m_im /= val;
		return *this;
	}
	friend complex operator+ (const double left, const complex& right)
	{
		return complex(left + right.m_re, right.m_im);
	}
	friend complex operator- (const double left, const complex& right)
	{
		return complex(left - right.m_re, -right.m_im);
	}
	friend complex operator* (const double left, const complex& right)
	{
		return complex(left * right.m_re, left * right.m_im);
	}
	friend complex operator/ (const double left, const complex& right)
	{
		const double denominator = right.m_re * right.m_re + right.m_im * right.m_im;
		return complex(left * right.m_re / denominator,
			-left * right.m_im / denominator);
	}
	//   Boolean operators
	bool operator== (const complex &other) const
	{
		return m_re == other.m_re && m_im == other.m_im;
	}
	bool operator!= (const complex &other) const
	{
		return m_re != other.m_re || m_im != other.m_im;
	}
	bool operator== (const double val) const
	{
		return m_re == val && m_im == 0.;
	}
	bool operator!= (const double val) const
	{
		return m_re != val || m_im != 0.;
	}
	friend bool operator== (const double left, const complex& right)
	{
		return left == right.m_re && right.m_im == 0.;
	}
	friend bool operator!= (const double left, const complex& right)
	{
		return left != right.m_re || right.m_im != 0.;
	}
};
#endif

//=================================================================================================
//====================complex.cpp (6º algorithm):==================================================
//=================================================================================================

//   Include header file
#include "complex.h"
//   Imaginary unity constants
const complex complex::i(0., 1.);
const complex complex::j(0., 1.);

//=================================================================================================
//====================dft.h (6º algorithm):========================================================
//=================================================================================================

#ifndef __DFT_H__
#define __DFT_H__
#include <complex>
using namespace std;
typedef complex<double> comp;
// Gets the complex conjugate of every element 
void conjugate(comp *array, int size);
// Multiplies two vectors element by element
void multiply(comp *arr1, comp *arr2, comp *result, int size);
// Finds the convolution of two vectors
void convolution(comp *arr1, comp *arr2, comp *result, int size);
// Discrete fourier transform. size must be a power of 2
void fourier_transform(comp *array, int size);
// Inverse fourier transform. size must be a power of 2
void inverse_fourier_transform(comp *array, int size);
#endif
