#pragma once

#include "Waveform.h"
#include "ICycleWaveform.h"

// An ActionWaveform when Played or Cycled calls an arbitrary code function, 
// passing it an arbitrary argument

typedef bool (*ActionFunction)( void* argument );

class ActionWaveform : public Waveform
	, public ICycleWaveform
{
protected:
	void* Argument;
	ActionFunction Action;

public:

	// allocate space for samples to be initialized in by caller
	ActionWaveform( int count, ulong duration ){
	}

	// caller provides space for samples and fills them in
	ActionWaveform( int* samples, int count, ulong duration ){
	}

	virtual String ToString() { return "ActionWaveform"; }

	virtual void Play( AnalogWriter* writer ){
		( *Action )( Argument );
	}

	// the caller should call Cycle repeatedly until the action
	// returns true, which indicates the "waveform" is "complete".

	// an Action that performs some initialization will always simply
	// return true. But a polling Action may repeatedly return false 
	// until a particular condition becomes true.

	bool Cycle( AnalogWriter* writer ){
		return ( *Action )( Argument );
	}
};

// https://stackoverflow.com/questions/9410/how-do-you-pass-a-function-as-a-parameter-in-c
