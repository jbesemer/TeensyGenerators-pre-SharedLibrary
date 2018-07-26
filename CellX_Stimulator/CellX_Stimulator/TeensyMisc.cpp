#include "Config.h"


// LED ports //////////////////////////////////////////////////////////////////

int LEDONTIME = 500;	// msec

void show(int pinOff, int pinOn) {
	digitalWrite(pinOff, LOW);
	digitalWrite(pinOn, HIGH);
	delay(LEDONTIME);
}

void LedSet(int ledPin, int isOn) {
	digitalWrite(
		ledPin,
		(isOn == 0)
		? LOW
		: HIGH);
}

void LedOn(int ledPin) {
	digitalWrite(ledPin, HIGH);
}

void LedOff(int ledPin) {
	digitalWrite(ledPin, LOW);
}

// button port assignments ////////////////////////////////////////////////////

// this code assumes button shorts input pin to ground with internal pullup enabled.
// Thus button pressed means the pin is pulled LOW; else HIGH
#if TEENSY_LI

int AllButtons[] = {
	BUTTON1,
	BUTTON2,
	BUTTON3,
	BUTTON4,
	BUTTON_NONE,
};

int AnyButtonPressed() {
	for (int i = 0; AllButtons[i] != BUTTON_NONE; i++)
		if (ButtonPressed(AllButtons[i]))
			return AllButtons[i];

	return BUTTON_NONE;
}
#endif

int OppositeState(int state) {
	if (state == HIGH)
		return LOW;
	else
		return HIGH;
}

int ButtonPressed(int button) {
	return digitalRead(button) == LOW;
}

int ButtonReleased(int button) {
	return digitalRead(button) == HIGH;
}

// Misc. //////////////////////////////////////////////////////////////

int FreeRam()
{
	//	extern int __heap_start;
	extern int *__brkval;
	int v;
	return (int)&v - (int)__brkval;
	//	return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
	// https://learn.adafruit.com/memories-of-an-arduino/measuring-free-memory
}


// TODO: access LED and Buttons as groups:
// http://tronixstuff.com/2011/10/22/tutorial-arduino-port-manipulation/
// http://playground.arduino.cc/Learning/PortManipulation


void PrintFreeRam() {
	Serial.print("Free ram: ");
	Serial.println(FreeRam());
}
