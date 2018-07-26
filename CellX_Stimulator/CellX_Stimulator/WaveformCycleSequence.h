#pragma once

#include "Waveform.h"
#include "ICycleWaveform.h"

class WaveformCycleSequence : public Waveform
	, public ICycleWaveform
{
protected:
	ICycleWaveform** Waveforms;
	int Index = 0;		// to track index of current waveform

public:
	// allocate array for waveforms, to be filled in by caller
	WaveformCycleSequence( int count )
	{
		Waveforms = (ICycleWaveform**)Allocate( count * sizeof( Waveform* ) );
		Count = count;
		Index = 0;
	}

	// caller supplies waveforms array
	WaveformCycleSequence( ICycleWaveform** waveforms, int count )
	{
		Waveforms = waveforms;
		Count = count;
		Index = 0;
	}

	bool Cycle( AnalogWriter* writer ){
		// play out waveform and advance index

		if( Index >= Count )
			Index = 0;

		if( Waveforms[ Index ]->Cycle( writer ) ){
			Index++;
		}
	}
};
