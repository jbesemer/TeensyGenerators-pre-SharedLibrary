#pragma once

#include "Config.h"
#include "Button.Toggle.h"
#include "Blinker.h"

// monitors a button which toggles a "mode" on or off.
// 

class ToggleMode
{
protected:
	bool Active = 0;		// true iff mode is active

	ToggleButton ToggleActive;	// button to toggle mode

public:
	ToggleMode(int buttonPin) : ToggleActive(buttonPin)
	{
	}

	bool IsActive() { return Active; }
	void SetActive(int isActive);

	// overrides must call base method
	virtual void Loop();		// called from main loop; override implements mode when Active
protected:
	virtual void Startup();		// override implements when mode toggles on
	virtual void Shutdown();	// override implements when mode toggles off
};

// implements ToggleMode with a blinking LED to indicate when mode is Active

class ToggleModeBlink : public ToggleMode
{
protected:
	Blinker ActiveBlinker;

public:
	ToggleModeBlink(int buttonPin, int ledPin, int pattern, int bits, uint interval)
		: ToggleMode(buttonPin)
		, ActiveBlinker(ledPin, pattern, bits, interval)
	{
	}

	ToggleModeBlink(int buttonPin, int ledPin)
		: ToggleMode(buttonPin)
		, ActiveBlinker(ledPin, 1, 2, 50)
	{
	}

	// overrides must call base method
	virtual void Loop();		// implements mode when Active
protected:
	virtual void Startup();		// implement when mode toggles on
	virtual void Shutdown();	// implement when mode toggles off
};
