#pragma once

#include "Waveform.h"

// FramedWaveform -- after playing the supplied waveform 
//		the last sample is held for the remainder of the overall duration

class FramedWaveform : public Waveform
{
public:
	Waveform* TheWaveform;
	ulong Duration;	// waveform plays then last sample is held until this overall duration elapses

	FramedWaveform(){}

	// caller owns waveform
	FramedWaveform( Waveform* waveform, ulong duration ){
		TheWaveform = waveform;
		Duration = duration;
	}

	void Play( Generator* generator );
};
