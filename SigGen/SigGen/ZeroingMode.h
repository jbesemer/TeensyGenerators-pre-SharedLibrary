#pragma once

#include "Config.h"

class ZeroingMode
{
	bool Zeroing = 0;	// true iff zeroing

public:
	bool IsZeroing() { return Zeroing; }
	void SetZeroing( int zeroingMode );

	void StartZeroing();
	void StopZeroing();

	void Loop();
};
