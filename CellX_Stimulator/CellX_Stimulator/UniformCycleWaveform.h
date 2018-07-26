#pragma once

#include "UniformWaveform.h"
#include "ICycleWaveform.h"

// A UniformWaveformCycle plays back a UniformWaveform in pieces

class UniformCycleWaveform : public UniformWaveform
	, public ICycleWaveform
{
protected:
	elapsedMicros Actual;	// actual elapsed time since start of waveform
	ulong Expected;			// expected elapsed time until next Sample
	int Index;				// index of next sample

public:
	virtual void Reset() {
		// Actual == Expected, means the test (>=) at the start of Cycle 
		// will succeed immediately and output the first sample soon as Cycle is called.
		Actual = 0;
		Expected = 0;
		Index = 0;
	}

	UniformCycleWaveform( int count, ulong duration )
		: UniformWaveform( count, duration )
	{
		Reset();
	}

	// caller provides space for samples and fills them in
	UniformCycleWaveform( int* samples, int count, ulong duration )
		: UniformWaveform( samples, count, duration )
	{
		Reset();
	}

	bool Cycle( AnalogWriter* writer ){
		// nothing to do until Actual time is after the Expected next event time
		if( Actual >= Expected ){

			if( Index >= Count ){
				// Index >= Count means we sent the last sample in the PREVIOUS cycle,
				// AND furthermore it's scheduled duration has elapsed;
				// so the sequence is truly complete.

				Reset();	// next sample will be the first one
							// Index = 0;	// next sample will be the first one

				return 1;	// signal Completion 
							// we do this BEFORE sending first sample. the caller may restart
							// the sequence immediately or do something else.
			}

			// output next sample
			uint value = Samples[ Index++ ];
			writer->Write( value );
			Expected += Duration;
		}

		return 0;			// "my safe word is 'keep going'"
	}
};

