#pragma once

#include "UniformWaveform.h"

// cache the DAC values for a sine wave. Arithmetic is necessarily done in floating point,
// though the domain and the resulting cache values are converted to DAC levels.
// 		count = number of samples for a single cycle (0..2pi)
// 		duration = hold time for each sample

class SineWaveform : public UniformWaveform
{
protected:
	String Prefix;
	String Suffix;

	void Init( float amplitude, float offset );
	SineWaveform( int count );

	// change play-out durations or frequency without recomputing waveforms

	void SetFrequency( float frequency );
	void SetDuration( float duration );

public:
	SineWaveform( float amplitude, float offset, int count, ulong duration );
	SineWaveform( float amplitude, float offset, int count, float hertz );

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
