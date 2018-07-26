#pragma once

#include "UniformWaveform.h"

#ifndef TWO_PI
#define TWO_PI ( 3.14159 * 2 )		// https://en.wikipedia.org/wiki/Unit_circle
#endif

// cache the DAC values for a sine wave. Arithmetic is necessarily done in floating point,
// though the domain and the resulting cache values are converted to DAC levels.
// 		count = number of samples for a single cycle [0..2pi)
// 		duration = hold time for each sample, microseconds

class SineWaveform : public UniformWaveform
{
protected:
	String Prefix;
	String Suffix;

	void Init( float amplitude, float offset );
	void Init( float amplitude, float offset, float start, float stop );
	
	// this method merely allocates space for a waveform; 
	// duration and actual data must be supplied by caller

	SineWaveform( int count )
		: UniformWaveform( count, 100 )
	{
	}

	// The signatures of constructor pairs are subtlely different, only 
	// differing in the type of the last parameter. Not a problem when variables
	// are supplied, but use the optional L or F suffix to disambiguate literals.

	// set duration in microseconds
	SineWaveform( int count, ulong duration )
		: SineWaveform( count )
	{
		SetDuration( duration );
	}

	// convert frequency in hertz to duration in microseconds
	SineWaveform( int count, float hertz )
		: SineWaveform( count )
	{
		SetFrequency( hertz );
	}

	// change play-out durations or frequency without recomputing waveforms

	void SetFrequency( float frequency );
	void SetDuration( float duration );

public:
	// Constructors ///////////////////////////////////////////////////////

	// one full sine wave cycle

	SineWaveform( float amplitude, float offset, int count, ulong duration )
		: SineWaveform( count, duration )
	{
		Init( amplitude, offset );
	}

	SineWaveform( float amplitude, float offset, int count, float hertz )
		: SineWaveform( count, hertz )
	{
		Init( amplitude, offset );
	}

	// arbitrary sine wave cycle, with starting and ending phase angles in degrees

	SineWaveform( float amplitude, float offset, float starting, float ending, int count, ulong duration )
		: SineWaveform( count, duration )
	{
		Init( amplitude, offset, starting, ending );
	}

	SineWaveform( float amplitude, float offset, float starting, float ending, int count, float hertz )
		: UniformWaveform( count, hertz )
	{
		Init( amplitude, offset, starting, ending );
	}

	// Period (Sec.) == duration (Sec.) * count
	//		== duration (microsec) / 1e6 * count
	// frequency (Hz) = 1 / Period (Sec.)
	//		== 1e6 / Period (uSec)
	//		== 1e6 / ( duration (uSec) * count )

	// frequency (Hz) == 1e6 / ( duration (uS) * count )
	// <=> duration (uS) == 1e6 / ( frequency (Hz) * count )

	static ulong Duration_uS( float frequency_Hz, int count ) {
		return 1e6 / ( frequency_Hz * count );
	}

	static float Frequency_Hz( long duration_uS, int count ) {
		return 1e6 / ( duration_uS * count );
	}

	ulong Duration_uS( float frequency_Hz ) {
		return 1e6 / ( frequency_Hz * Count );
	}

	float Frequency_Hz( long duration_uS ) {
		return 1e6 / ( duration_uS * Count );
	}

	String ToString(){ return "Sine "+ Prefix + Suffix; }

	// ExampleSineWave ////////////////////////////////////////////////////

	static SineWaveform ExampleSineWave;

};
