#pragma once

#include "Waveform.h"

// An ArbitraryWaveform is a sequence of Samples,
//	each a level of arbitrary duration

class ArbitraryWaveform : public Waveform
{
protected:
	Sample* Samples;	// array of Samples (value, duration pairs)

	ArbitraryWaveform();

public:
	// allocate space for samples to be initialized in by caller
	ArbitraryWaveform( int count );

	// caller provides space for samples and fills them in
	ArbitraryWaveform( Sample* samples, int count );

	virtual String ToString() { return "ArbitraryWaveform"; }

	virtual void Play( AnalogWriter* writer );

	void Set( int index, ulong duration, int value );

	void Print();
};
