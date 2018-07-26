#include "ToggleMode.h"

// Blinker ZeroBlinker(ZERO_LED, 1, 2, 50);
// ToggleButton ActivationButton(ZERO_BUTTON);

// ToggleMode base

void ToggleMode::SetActive(int isActive)
{
	ToggleActive.ToggleState = isActive;
	if (isActive)
		Startup();
	else
		Shutdown();
}

void ToggleMode::Loop() {
	if (ToggleActive.WasToggledOn())
		Startup();

	else if (ToggleActive.WasToggledOff())
		Shutdown();

	// subclass overrides, calls base, 
	// and then implements mode when Active
}

void ToggleMode::Startup()
{
	if (!Active) {
		Active = 1;
	}
}

void ToggleMode::Shutdown()
{
	if (Active) {
		Active = 0;
	}
}

// ToggleModeBlink

void ToggleModeBlink::Loop() {
	ToggleMode::Loop();

	if (Active) {
		ActiveBlinker.Loop();
	}

	// subclass overrides, calls base, 
	// and then implements mode when Active
}

void ToggleModeBlink::Startup()
{
	if (!Active) {
		ActiveBlinker.Start();
	}

	// above test before calling base, to catch rising edge
	ToggleMode::Startup();
}

void ToggleModeBlink::Shutdown()
{
	if (Active) {
		ActiveBlinker.Shutdown();
	}

	// above test before calling base, to catch falling edge
	ToggleMode::Shutdown();
}

