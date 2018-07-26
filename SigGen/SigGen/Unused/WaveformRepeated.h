//	WaveformRepeated -- play a waveform repeatedly for a given overall duration

#ifndef _REPEATEDWAVEFORM_h
#define _REPEATEDWAVEFORM_h

#include "Waveform.h"

class WaveformRepeated
{
 protected:

 public:
	Waveform* TheWaveform;
	ulong Duration;	// waveform repeats until this overall duration elapses
	elapsedMicros Elapsed;
	bool IsExpired(){ return Elapsed > Duration; }

	WaveformRepeated( Waveform* waveform, ulong duration ){
		TheWaveform = waveform;
		Duration = duration;
	}

	void Play( Generator* dacOut );

	virtual String ToString() {
		String r = "Repeated ";
		r.append( TheWaveform->ToString() );
		return r;
	}
};

#endif

