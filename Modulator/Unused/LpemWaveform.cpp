#include "LpemWaveform.h"
#include "Generator.h"


void LpemWaveform::Init(
	// these are adc count levels
	uint baselevel,	// the starting level
	uint peaklevel,	// the peak level at the top of the waveform
	uint finallevel,// the ending level at the end of the waveform

	// these are durations, in MILLISECONDS, and uint, not ulong
	uint risetime,	// risetime base to peak
	uint sustain,	// duration of peaklevel
	uint falltime)	// falltime peak to finallevel
{
}


void LpemWaveform::Play( Generator* generator )
{
	Sample* current = Samples;
	elapsedMillis elapsed;
	ulong time = 0;

	for( int i = 0; i < Count; i++ ){
		ulong duration = current->Duration;
		uint value = current->Value;
		current++;

		generator->DacWrite( value );

		time += duration;
		while( time > elapsed )
			continue;
	}
}
