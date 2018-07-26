#pragma once

#include "Waveform.h"

class WaveformSequence : public Waveform
{
protected:
	Waveform** Waveforms;
	int Index = 0;		// to track index of current waveform

public:
	// allocate array for waveforms, to be filled in by caller
	WaveformSequence( int count );

	// caller supplies waveforms array
	WaveformSequence( Waveform** Waveforms, int count );

	virtual void Play( AnalogWriter* writer );

	String ToString(){ return "WaveformSequence"; }
};
