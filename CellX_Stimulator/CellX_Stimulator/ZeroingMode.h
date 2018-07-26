#pragma once
#include "ToggleMode.h"
#include "AnalogWriter.h"

class ZeroingMode : public ToggleModeBlink
{
public:
	ZeroingMode(int buttonPin, int ledPin) 
		: ToggleModeBlink(buttonPin, ledPin, 1, 2, 50) {}

	void Startup();
	void Shutdown();
};
