#pragma once

#include "UniformWaveform.h"

class StairWaveform : public UniformWaveform
{
	void Init( int count, int startLevel, int stepLevel );

	String Description;
public:
	StairWaveform( int count, int startLevel, int stepLevel, ulong stepDuration )
		: UniformWaveform( count, stepDuration )
	{
		Init( count, startLevel, stepLevel );
	}

	virtual String ToString() { return "StepWaveform"; }	// code/doc mis-match
};
