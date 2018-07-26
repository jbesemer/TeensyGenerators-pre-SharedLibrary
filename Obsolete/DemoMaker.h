#pragma once

#include <WProgram.h>
#include "Config.h"
#include "Waveform.h"
//#include "Generator.h"

class Generator;

class DemoMaker
{
	// ms timer for mode changes
	elapsedMillis msElapsed = 0;
	unsigned int generatorTime = 2000;	// change waveform every 2 seconds

public:
	static Waveform* Waveforms[];
	static int Count;

	DemoMaker();
	bool IsRunning;
	int Index;

	Waveform* First(){ return Waveforms[ 0 ]; }
	Waveform* Last(){ return Waveforms[ Count - 1 ]; }

	void Loop( Generator* generator );
};

