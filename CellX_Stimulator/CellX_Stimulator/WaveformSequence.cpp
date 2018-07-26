#include "WaveformSequence.h"

// A WaveformSequence is a sequence of Waveforms,
//	each a level of arbitrary width/duration

WaveformSequence::WaveformSequence( int count )
{
	Waveforms = (Waveform**)Allocate( count * sizeof( Waveform* ) );
	Count = count;
	Index = 0;
}

WaveformSequence::WaveformSequence( Waveform** waveforms, int count )
{
	Waveforms = waveforms;
	Count = count;
	Index = 0;
}

// the expectation is that Run plays out a single waveform cycle and returns.
// other polling and animation happens between calls to Run.
// So this method plays one of the waveforms, as expected, and 
// manages state so that each subsequent call plays the next waveform.

void WaveformSequence::Play( AnalogWriter* writer )
{
	// play out waveform and advance index

	if( Index >= Count )
		Index = 0;

	Waveforms[ Index++ ]->Play( writer );
}
