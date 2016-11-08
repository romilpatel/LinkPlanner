# ifndef PROGRAM_INCLUDE_PIN_H_
# define PROGRAM_INCLUDE_PIN_H_

# include <math.h>       /* pow */
# include "netxpto.h"


// Implements a Pin.
class Pin : public Block {

	/* State Variables */

	bool firstTime{ true };

 public:

	 /* Input Parameters */
	
	double inputOpticalPower{1e-3}; //potencia otica de entrada do bloco Pin
	double currentGain{1.0}; //Ganho de corrente do bloco Pin
	double inputCurrent{currentGain*inputOpticalPower}; //corrente eletrica de saida do bloco Pin (i=R*|Popt|)
	
	 /* Methods */
	 Pin() {}; //nao sei
	 Pin(vector<Signal *> &InputSig, vector<Signal *> &OutputSig) :Block(InputSig, OutputSig){}; //nao sei

	 void initialize(void); //?
	 bool runBlock(void); //?
	 
	 
	 void setGain(double gain) { currentGain=gain; } //Ajustar ganho do bloco Pin
/*
	 void setOutputOpticalPower(double outOpticalPower) { outputOpticalPower = outOpticalPower; }  //ganho?
	 void setOutputOpticalPower_dBm(double outOpticalPower_dBm) { outputOpticalPower = 1e-3*pow(10, outOpticalPower_dBm / 10); }

	 void setOutputOpticalWavelength(double outOpticalWavelength) { outputOpticalWavelength = outOpticalWavelength; outputOpticalFrequency = SPEED_OF_LIGHT / outOpticalWavelength; }
	 void setOutputOpticalFrequency(double outOpticalFrequency) { outputOpticalFrequency = outOpticalFrequency; outputOpticalWavelength = outOpticalFrequency / outputOpticalFrequency; }
*/

};

# endif // PROGRAM_INCLUDE_netxpto_H_


