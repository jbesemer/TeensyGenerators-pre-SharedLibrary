#pragma once

#include "Waveform.h"

// A ICycleWaveform is an interface for playing back the 
// waveform incrementally, instead of all at once

// https://stackoverflow.com/questions/1216750/how-can-i-simulate-interfaces-in-c

class ICycleWaveform 
{
protected:
#if PREMATURE_OPTIMIZATION
	// optional mechanism for caching the Writer, so it doesn't have to be passed as an arg for each call to Cycle
	AnalogWriter* Writer;
	void SetWriter( AnalogWriter* writer ){ Writer = writer; }
#endif

public:


	// send 0 or more samples to the Writer,
	// return true iff the entire waveform has been sent

	virtual bool Cycle( AnalogWriter* writer ) = 0;
};
