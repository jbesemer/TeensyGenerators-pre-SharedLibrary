#pragma once

#include "Waveform.h"
#include "UniformWaveform.h"

class PlayLoop : public UniformWaveform
{
protected:
	UniformWaveform* Waveform;
	AnalogWriter* Writer;

	elapsedMicros Actual;	// actual elapsed time since start
	ulong Expected;			// expected elapsed time until next Sample
	int Index;				// index of next sample

public:

	bool IsComplete(){ return ( Index >= Count ); }

	PlayLoop( UniformWaveform* waveform, AnalogWriter* writer ) {
		Waveform = waveform;
		Writer = writer;
		Reset();
	}

	virtual String ToString() { return "UniformWaveform"; }

	virtual void Reset() {
		Actual = 0;
		Expected = 0;
		Index = 0;
	}

	// play the next sample when it's time; 
	//
	// returns true after playing the last sample in the sequence 
	// (that is, after the value was output and its duration expired).
	//
	// In this case, the first sample will have been output, and the 
	// Play Loopmachinery is reset to replay the sequence, if continued.

	virtual int Loop()
	{
		if( Actual >= Expected ){
			// output next sample
			uint value = Samples[ Index++ ];
			Writer->Write( value );
			Expected += Duration;

			if( Index >= Count ){
				Reset();
				return 1;	// sequence complete
			}
		}

		return 0;			// more to play or wait
	}
}
