#pragma once

extern void TeensyCellX_Setup();

extern int FreeRam();
extern void PrintFreeRam();

extern int LEDONTIME;

extern void show(int pinOff, int pinOn);
extern void LedSet(int ledPin, int isOn);
extern void LedOn(int ledPin);
extern void LedOff(int ledPin);


// return the other state
extern int OppositeState(int state);

// return 1 iff button is ...
extern int ButtonPressed(int button);		// ...pressed (input is LOW)
extern int ButtonReleased(int button);	// ...released (input is HIGH)

										// return 1 if any of the 4 buttons are pressed
extern int AnyButtonPressed();


