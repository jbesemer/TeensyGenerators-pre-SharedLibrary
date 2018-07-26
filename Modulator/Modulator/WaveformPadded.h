#pragma once

#include "Waveform.h"

// WaveformPadded -- after playing the supplied waveform 
//		the last sample is held for the remainder of the overall duration

class WaveformPadded : public Waveform
{
public:
	Waveform* TheWaveform;
	ulong Duration;

	WaveformPadded(){}

	// caller owns waveform
	WaveformPadded( Waveform* waveform, ulong duration ){
		TheWaveform = waveform;
		Duration = duration;
	}

	virtual String ToString() {
		String r = "Padded ";
		r.append( TheWaveform->ToString() );
		return r;
	}

	virtual void Play( AnalogWriter* writer );
};
