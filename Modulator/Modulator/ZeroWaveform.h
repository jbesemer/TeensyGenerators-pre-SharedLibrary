#pragma once

#include "UniformWaveform.h"

#define ZERO_DURATION_DEFAULT 1000

// ZeroWaveform is defined continuous 0 sent out DAC

// there's no longer a need for a zero waveform; 
// it's been supplanted by zeroing mode in the Generator

class ZeroWaveform : public UniformWaveform
{
	void Init();

public:
	ZeroWaveform();
	ZeroWaveform( ulong duration );

	String ToString(){ return "ZeroWaveform"; }

	static ZeroWaveform Example;
};
