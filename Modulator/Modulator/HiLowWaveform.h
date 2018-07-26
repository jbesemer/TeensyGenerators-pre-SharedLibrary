#pragma once

#include "ArbitraryWaveform.h"

//	HiLowWaveform -- outputs a high value followed by a low value,
//		each of a specific duration

class HiLowWaveform : public ArbitraryWaveform
{
	void Init(int highValue, int lowValue, ulong highWidth, ulong lowWidth);

	int HighValue, LowValue;
	ulong HighWidth, LowWidth;

public:
	// if you're using one of the middle two below with literal constants, 
	// you need to be explicit with a UL suffix or an (int) cast prefix.

	HiLowWaveform(int highValue, int lowValue, ulong highWidth, ulong lowWidth)
		: ArbitraryWaveform(2)
	{
		Init(highValue, lowValue, highWidth, lowWidth);
	}

	// like previous but with zero for the low value

	HiLowWaveform(int amplitude, ulong highWidth, ulong lowWidth)
		: ArbitraryWaveform(2)
	{
		Init(amplitude, 0, highWidth, lowWidth);
	}

	// send 1st value, wait for pulseWidth, then output 2nd value and return with minimum delay

	HiLowWaveform(int highValue, int lowValue, ulong pulseWidth)
		: ArbitraryWaveform(2)
	{
		Init(highValue, lowValue, pulseWidth, 0);
	}

	// like previous but with zero for low value

	HiLowWaveform(int amplitude, ulong pulseWidth)
		: ArbitraryWaveform(2)
	{
		Init(amplitude, 0, pulseWidth, 0);
	}

	void Play(AnalogWriter* writer);

	String ToString();
};
