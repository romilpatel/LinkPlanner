#include <algorithm>
#include <complex>

#include "netxpto.h"
#include "bit_error_rate.h"

void BitErrorRate::initialize(void){
	firstTime = false;

	outputSignals[0]->setSymbolPeriod(inputSignals[0]->getSymbolPeriod());
	outputSignals[0]->setSamplingPeriod(inputSignals[0]->getSamplingPeriod());
	outputSignals[0]->setFirstValueToBeSaved(inputSignals[0]->getFirstValueToBeSaved());
}


<<<<<<< HEAD
<<<<<<< HEAD
bool BitErrorRate::runBlock(void){
=======
bool BitErrorRate::runBlock(void) {
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
bool BitErrorRate::runBlock(void){
>>>>>>> Romil

	/* Computing z */ // This code converges in below 10 steps, exactness chosen in order to achieve this rapid convergence
	if (firstPass)
	{
		firstPass = 0;
		double x1 = -2;
		double x2 = 2;
		double x3 = x2 - (erf(x2 / sqrt(2)) + 1 - alpha)*(x2 - x1) / (erf(x2 / sqrt(2)) - erf(x1 / sqrt(2)));
		double exacteness = 1e-15;

<<<<<<< HEAD
<<<<<<< HEAD
		while (abs(erf(x3 / sqrt(2)) + 1 - alpha)>exacteness)
=======
		while (abs(erf(x3 / sqrt(2)) + 1 - alpha) > exacteness)
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
		while (abs(erf(x3 / sqrt(2)) + 1 - alpha)>exacteness)
>>>>>>> Romil
		{
			x3 = x2 - (erf(x2 / sqrt(2)) + 1 - alpha)*(x2 - x1) / (erf(x2 / sqrt(2)) - erf(x1 / sqrt(2)));
			x1 = x2;
			x2 = x3;
		}

		z = -x3;

	}


	int ready1 = inputSignals[0]->ready();
	int ready2 = inputSignals[1]->ready();
	int ready = min(ready1, ready2);
	int space = outputSignals[0]->space();

	int process = min(ready, space);

	
	/* Outputting final report */

	if (process == 0)
	{

		/* Calculating BER and bounds */

<<<<<<< HEAD
<<<<<<< HEAD
		double BER = (recievedBits - coincidences) / recievedBits;
=======
<<<<<<< HEAD
		double BER = (recievedBits - coincidences) / recievedBits;
=======
		t_real NumberOfBits = receivedBits;
		t_real Coincidences = coincidences;

		t_real BER;
		BER = (NumberOfBits - Coincidences) / NumberOfBits;
>>>>>>> AnaLuisa
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
		double BER = (recievedBits - coincidences) / recievedBits;
>>>>>>> Romil

		double UpperBound = BER + 1 / sqrt(recievedBits) * z  * sqrt(BER*(1 - BER)) + 1 / (3 * recievedBits)*(2 * z * z * (1 / 2 - BER) + (2 - BER));
		double LowerBound = BER - 1 / sqrt(recievedBits) * z  * sqrt(BER*(1 - BER)) + 1 / (3 * recievedBits)*(2 * z * z * (1 / 2 - BER) - (1 + BER));

		/* Outputting a .txt report*/
		ofstream myfile;
		myfile.open("BER.txt");
		myfile << "BER= " << BER << "\n";
		myfile << "Upper and lower confidence bounds for " << (1 - alpha)*100 << "% confidence level \n";
		myfile << "Upper Bound= " << UpperBound << "\n";
		myfile << "Lower Bound= " << LowerBound << "\n";
		myfile << "Number of received bits =" << recievedBits << "\n";
		myfile.close();
		return false;
	}



	for (long int i = 0; i < process; i++) {

		t_binary signalValue;
		inputSignals[0]->bufferGet(&signalValue);
		t_binary SignalValue;
		inputSignals[1]->bufferGet(&SignalValue);

		/* Outputting mid reports */
		if (m > 0)
		{
<<<<<<< HEAD
<<<<<<< HEAD
			if ((remainder(recievedBits, m) == 0) & (recievedBits>0))
=======
<<<<<<< HEAD
			if ((remainder(recievedBits, m) == 0) & (recievedBits>0))
=======
			if (remainder(receivedBits, m) == 0 && receivedBits>0)
>>>>>>> AnaLuisa
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
			if ((remainder(recievedBits, m) == 0) & (recievedBits>0))
>>>>>>> Romil
			{
				n++;

				ostringstream oss;
				oss << "midreport" << n << ".txt";
				string filename = oss.str();

				/* Calculating BER and bounds */

<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
=======
				t_real NumberOfBits = receivedBits;
				t_real Coincidences = coincidences;
>>>>>>> AnaLuisa
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil

				double BER;
				BER = (recievedBits - coincidences) / recievedBits;

				double UpperBound = BER + 1 / sqrt(recievedBits) * z  * sqrt(BER*(1 - BER)) + 1 / (3 * recievedBits)*(2 * z * z * (1 / 2 - BER) + (2 - BER));
				double LowerBound = BER - 1 / sqrt(recievedBits) * z  * sqrt(BER*(1 - BER)) + 1 / (3 * recievedBits)*(2 * z * z * (1 / 2 - BER) - (1 + BER));

				/* Outputting a .txt report*/
				ofstream myfile;
				myfile.open(filename);
				myfile << "BER= " << BER << "\n";
				myfile << "Upper and lower confidence bounds for" << 1-alpha << "confidence level \n";
				myfile << "Upper Bound= " << UpperBound << "\n";
				myfile << "Lower Bound= " << LowerBound << "\n";
				myfile << "Number of received bits =" << recievedBits << "\n";
				myfile.close();
			}
		}

<<<<<<< HEAD
<<<<<<< HEAD
		recievedBits++;
=======
<<<<<<< HEAD
		recievedBits++;
=======
		receivedBits++;
>>>>>>> AnaLuisa
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
		recievedBits++;
>>>>>>> Romil

		if (signalValue == SignalValue)
		{
			coincidences++;
<<<<<<< HEAD
<<<<<<< HEAD
=======
<<<<<<< HEAD
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
>>>>>>> Romil
			outputSignals[0]->bufferPut((t_binary) 1);
		}
		else
		{
			outputSignals[0]->bufferPut((t_binary) 0);
<<<<<<< HEAD
<<<<<<< HEAD
=======
>>>>>>> Romil
		}

	}
	return true;

<<<<<<< HEAD
}
=======
=======

			outputSignals[0]->bufferPut(1);

			translate2 << 1 << "\n";
		}
		else
		{

			outputSignals[0]->bufferPut(0);

			translate2 << 0 << "\n";
>>>>>>> AnaLuisa
		}

	}
		return true;

	}
>>>>>>> 526292907dd2ff7d6ea618152856721b6b80e5dd
=======
}
>>>>>>> Romil
