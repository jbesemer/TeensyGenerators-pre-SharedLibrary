//	WaveformRepeated -- play a waveform repeatedly for a given overall duration

#include "WaveformRepeated.h"

void WaveformRepeated::Play( Generator* generator )
{
	Elapsed = 0;
	while( !IsExpired() )
		TheWaveform->Play( generator );
}
