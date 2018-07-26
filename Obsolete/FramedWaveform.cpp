#include "FramedWaveform.h"

void FramedWaveform::Play( Generator* generator )
{
	elapsedMicros elapsed;

	// run the waveform
	TheWaveform->Play( generator );

	// pad out the remainder of the frame with whatever was the last sample 
	// in the waveform. returns immediately if the original waveform takes longer
	// than the frame length to play out.

	while( Duration > elapsed )
		continue;

	// TODO: could break this into two-states to reduce latency for very long frames
}
