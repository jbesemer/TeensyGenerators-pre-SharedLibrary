#pragma once

#include "Waveform.h"

// A FixedWaveform outputs a fixed level for a specific duration


#define DEFAULT_DURATION 10000

class FixedWaveform : public Waveform
{
protected:
	int Sample;		// the output level
	ulong Duration;	// duration 

public:
	// output level for specific duration
	FixedWaveform( int level, ulong duration );

	// output level for DEFAULT_DURATION
	FixedWaveform( int level );


	// output 0 for DEFAULT_DURATION
	FixedWaveform();

	virtual String ToString() { return "FixedWaveform"; }

	virtual void Play( AnalogWriter* writer );
};
