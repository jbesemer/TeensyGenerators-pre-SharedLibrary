#pragma once

#include "Config.h"

// turn on an led and then off again after a given interval

// code assumes LED wired to pin in ACTIVE HIGH configuration

class LedOneShot
{
	// constants

	int Pin;		// pin to change
	int Duration;	// on time duration

	// variables

	bool IsOn;		// is led on or off
	int Index;		// state (index of next output bit)

	elapsedMillis elapsed;	// elapsed time since last change

public:

	LedOneShot( int pin, int interval ){
		Pin = pin;
		Interval = interval;

		pinMode( pin, OUTPUT );
	}

	// control LED

	void Write( int bit ){ digitalWrite( Pin, bit ? HIGH : LOW ); }
	void On(){ digitalWrite( Pin, HIGH ); }
	void Off(){ digitalWrite( Pin, LOW ); }

	// control blinking

	void Stop(){ Blinking = false; }
	void Start(){ Blinking = true; }

	void Loop(){
		if( Blinking
			&& elapsed > (unsigned)Interval ){
			elapsed = 0;
			int bit = ( Pattern >> Index ) & 1;
			Index++;
			Index %= Bits;
			Write( bit );
		}
	}

	// stop and ensure specific final state

	void Shutdown( int isOn = 0 ){
		Stop();
		Write( isOn );
	}
};
