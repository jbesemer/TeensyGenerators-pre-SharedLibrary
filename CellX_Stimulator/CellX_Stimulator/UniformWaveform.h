#pragma once

#include "Waveform.h"

// A UniformWaveform is a sequence of levels of uniform duration

class UniformWaveform : public Waveform
{
protected:
	int* Samples;	// array of sample values
	ulong Duration;	// duration of each sample

public:

	// allocate space for samples to be initialized in by caller
	UniformWaveform( int count, ulong duration );

	// caller provides space for samples and fills them in
	UniformWaveform( int* samples, int count, ulong duration );

	virtual String ToString() { return "UniformWaveform"; }

	virtual void Play( AnalogWriter* writer );

	void Set( int index, int sample );

	void Print();
};
