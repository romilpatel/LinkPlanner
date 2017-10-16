
#include<iostream>

using namespace std;

#include "netxpto.h";

#include "local_oscillator.h";
#include "photodiode.h";
#include "sink.h";

int main()
{


	// SIGNALS
	OpticalSignal S0("S0.sgn");
	TimeContinuousAmplitudeContinuousReal S9("S9.sgn");



	// BLOCKS
	LocalOscillator B0{ vector<Signal*> {}, vector<Signal*> {&S0} };

	Photodiode B1{ vector<Signal*> {&S0}, vector<Signal*> {&S1} };

	Sink B2{ vector<Signal*> {&S1}, vector<Signal*> {} };
	B2.setNumberOfSamples(samplesPerSymbol*numberOfBitsGenerated);
	B2.setDisplayNumberOfSamples(true);

	System MainSystem{ vector<Block*> {&B0, &B1, &B2} };


    return 0;
}