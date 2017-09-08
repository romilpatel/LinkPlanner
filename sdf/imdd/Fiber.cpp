//========================================
//====Author: Vlad Zubets=================
//====E-mail: uladzislau.zubets@ua.pt=====
//============21/11/2016==================
#include <limits>
#include <complex> // numero complexo
#include <stdio.h> // *printf*
#include <iostream>
#include <string>
#include <math.h> // *exp*
#include <algorithm> //std::min_element, std::max_element
#include <fstream> // isso e para imprimir e gravar no ficheiro txt
#include <valarray>

#include "myfft.cpp"
#include "fftshift.cpp"

using namespace std;
using std::cout; // cout--> consoule output de informacao
using std::endl; // end line
//===========================================================================================================
//===========================================================================================================
int main()
{
  double Pi = 3.98; // valor de entrada em mW 
  double alpha = 0.25; // valor de perdas na fibra 
  double t = 200e-12; // valor da largura de pulso de entrada em segundos (largura a meia altura)
  double dt = 1e-12; // intervalo do periodo
  double Area = 6.756e-5; // valor da area efetiva do nucleo em m^2
  double C = 0; // valor de chirp factor
  double Lambda = 1550e-9; // valor C.D.O. em metros
  double D = -10.0; // valor d coeficiente de dispersao em ps/nm/km D=-/2*pi*c*B2)/(lambda^2)
  double s = 100.0; // comprimento de fibra em Km
  const double c = 3e8; // velocidade de luz
  double n1 = 1.48; // indice de refracao de revestimento
  double n2 = 7e-10; // indice de refracao de nucleo
  const double pi = 3.1415926535897932384; // valor de pi
  complex < double > z( 0.0, 1.0 );     // z = 0 + 1i definicao do numero complexo
  double h = 2000.0; // passo h
  typedef std::complex<double> Complex;
  typedef std::valarray<Complex> CArray;
//==============================================================================================================
//==============================================================================================================
  double A = alpha/(4.343); //vem da referencia
  double f = c/Lambda; // calcula a frequencia da onda EM
  double omega = 2*pi*f; // frequencia angular (w)
  double a = n2*omega; // primeira parte para calcular gamma
  double b = c*Area; // segunda parte para calcular gamma
  double gamma = a/b; // calcula gamma, ou seja, coeficiente nao-linear
  double B2 = -((pow(Lambda,2))*D)/(2*pi*c); // calcula o coeficiente de dispersao de velocidade de grupo (B2<0-->dispersao anomala, B2>0-->dispersao normal)
  double L = (pow(t,2))/(abs(B2)); // comprimento de dispersao
  double Ao = sqrt(Pi); // amplitude do impulso de entrada de Gauss
//=========================================================================================================================
//=========================================================================================================================
//==================================PROCESSO DE CRACAO DE FEIXE DE GAUSS==================================================
//=========================================================================================================================
//=========================================================================================================================
  ofstream myfile1;
  myfile1.open ("feixe_de_entrada.txt");

  ofstream myfile2;
  myfile2.open ("fft_de_At.txt"); 
  
  ofstream myfile3;
  myfile3.open ("ifft_de_At.txt"); 
  
  int l = 8192; // e dimensao do vetor At
  
  //double maxAt = std::numeric_limits<float>::min(); // para encontrar valor maximo de At
  
  //double At[l] = {0}; // indice inicial de vetor At 

  Complex At[l]; // declaracao que (At) e um numero complexo com a dimensao (l)

  //double abs_At[l] = {0}; // indice inicial de abs de At
  
  unsigned int i = 0;
  
  Complex I=1i;
  
  for (double tau = -4096e-12; tau < 4095e-12; tau+=1e-12) // Qual é o tempo upper(U), lower(L) e intervalo entre intervalo upper e  lower intervalo(I)
  { 
      i++;
  	
      At[i] = Ao*exp(-((1.0+I*C)/2.0)*(tau/t)*(tau/t)); // geracao do impulso de entrada de Gauss
//================================================================================================================== 
      //if(maxAt < At[i]) // para encontrar valor maximo de At
      //{
      //      maxAt = At[i]; // para encontrar valor maximo de At
	  //}
	  //abs_At[i] = fabs(At[i]); // abs de At
//=============================================================================================================================  
      myfile1 << tau; myfile1 << "       "; myfile1 << abs(At[i]); myfile1 << "\n"; // para imprimir e gravar no ficheiro txt (feixe de entrada)
  }
//=================================================================================================================================
//=================================================================================================================================
//================PROCESSO DE CALCULO DE FFT DE FEIXE DE GAUSS=====================================================================
//=================================================================================================================================
//=================================================================================================================================
  CArray semi_spectrum(At, l); // declara qual e vetor de entrada (At) e a dimensao dele (l) ainda nao dividido por 1000
  fft(semi_spectrum); // ponha o vetor At dentro da fft no ficheiro myfft.cpp
  	
  CArray spectrum(At, l); // declara qual e vetor de entrada (At) e a dimensao dele (l)
  
  for(int k=0; k<l; k++) // ciclo for para dividir por 1000 cada elemento individualmente
  {
	real(spectrum[k]) = real(semi_spectrum[k]/1000.0); // divide cada elemento real
	imag(spectrum[k]) = imag(semi_spectrum[k]/1000.0); // divide cada elemento imaginario
  }
  
  for(int k=0; k<l; k++) // isso e para gravar num ficheiro de txt
  {
		myfile2 << spectrum[k] << "\n";
  }  
//=====================================================================================================  
//=====================================================================================================
//============================PROCESSO DE CALCULO DE MANAKOV-PMD=======================================
//=====================================================================================================
//=====================================================================================================
  double dw = (1.0/l)/(dt*2.0*pi); // calcula a frequencia instantanea
  double w = (-1.0*l/2.0)*dw;
  	
  for (double m = 0.1 ; m < (s/10.0); m+=0.1) // diferentes comprimentos de fibra
  {
  	double X = m*L;
  	
       //for (double w = (-1.0*l/2.0)*dw ; w < ((l/2.0)-1.0)*dw; w+=1.0*dw) // criacao de pontos para a transformada de Fourier
       //{
            for (double j = h ; j < X; j+=h) // ciclo for para cada passo (h)
            {
            	for(int k=0; k<l; k++)
            	{
                  spectrum[k] = spectrum[k]*exp(-A*(h/2.0)+I*B2/2.0*w*w*(h)); // calcula a parte linear de Manakov
				}
                ifft(spectrum);
                for(int k=0; k<l; k++)
                {
                	spectrum[k] = spectrum[k]*exp(I*(8.0/9.0)*gamma*(abs(spectrum[k]))*(abs(spectrum[k]))*(h)); // calcula a parte nao linear de Manakov
				}
                fft(spectrum);
                for(int k=0; k<l; k++)
                {
                	spectrum[k] = spectrum[k]*exp(-A*(h/2.0)+I*B2/2.0*(w*w)*(h)); // calcula Manakov
				}
                w+=1.0*dw;
            }
       //}
      	ifft(spectrum);
        //fwhmo = find(abs(f) > abs(max(f)/2));
        //fwhmo = length(fwhmo);
        //pbratio(q) = fwhmo/fwhmi;
        //q = q+1;
  }

for(int k=0; k<l; k++) // para imprimir e gravar no ficheiro txt (feixe de saida)
    {    
	    myfile3 << abs(spectrum[k]) << "\n";
    }
//=====================================================================================================
//=====================================================================================================
  return 0; // conclusao satisfatoria
}
