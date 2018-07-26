#pragma once
#include "ArbitraryWaveform.h"

// an Lpem waveform is a curve which should be recognized as a slow pulse


class LpemWaveform :
	public ArbitraryWaveform
{
	// these are adc count levels

	uint baselevel;	// the starting level
	uint peaklevel;	// the peak level at the top of the waveform
	uint finallevel;// the ending level at the end of the waveform

	// these are uint (not ulong) durations, in MILLISECONDS

	uint risetime;	// risetime base to peak
	uint sustain;	// duration of peaklevel
	uint falltime;	// falltime peak to finallevel

	void Init( uint baselevel, uint peaklevel, uint finallevel,
		uint risetime, uint sustain, uint falltime );

public:

	LpemWaveform( uint baselevel, uint peaklevel, uint finallevel,
		uint risetime, uint sustain, uint falltime )
	{
		Init( baselevel, peaklevel, finallevel, risetime, sustain, falltime );
	}

	virtual void Play( Generator* generator );

	virtual String ToString() { return "LpemWaveform"; }
};

