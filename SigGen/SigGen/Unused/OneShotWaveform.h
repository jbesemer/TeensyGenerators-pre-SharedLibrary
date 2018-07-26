#pragma once

#include "Waveform.h"
#include "LiTeensy.h"

// OneShotWaveform waits for a button to be pressed and released
//		before playing the supplied waveform

class OneShotWaveform : public Waveform
{
	int Button;
	int MessageSent;

public:
	Waveform* TheWaveform;

	OneShotWaveform( Waveform* waveform ){
		TheWaveform = waveform;
		Button = BUTTON_NONE;
		MessageSent = 0;
	}

	void Play( Generator* generator );

	virtual String ToString() {
		String r = "OneShot of ";
		r.append( TheWaveform->ToString() );
		return r;
	}
};
