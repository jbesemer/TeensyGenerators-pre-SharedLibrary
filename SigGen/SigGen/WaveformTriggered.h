#pragma once

#include "Waveform.h"
#include "Button.h"
#include "Teensy.h"

// WaveformTriggered waits for a button to be pressed and released
//		before playing the supplied waveform

#if TEENSY_LI
class WaveformTriggered : public Waveform
{
	Button TriggerButton;
	bool Waiting;

public:
	Waveform* TheWaveform;

	WaveformTriggered( int button, Waveform* waveform )
		: TriggerButton( button )
	{
		TheWaveform = waveform;
		Waiting = false;
	}

	virtual void Play( AnalogWriter* writer );
	void Shutdown();

	virtual String ToString() {
		String r = "Triggered ";
		r.append( TheWaveform->ToString() );
		return r;
	}
};
#endif // TEENSY_LI
