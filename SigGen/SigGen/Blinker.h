#pragma once

#include "Config.h"

// blink an LED periodically with a specific pattern

// E.g; Blinker blinker( LED, 0x5, 10, 100 );  // blinks LED twice every sec: 

// code assumes LED wired to pin in ACTIVE HIGH configuration

class Blinker
{
public:

	// constants

	int Pin;		// pin to change
	int Pattern;	// bit pattern to send out (lsb first)
	int Bits;		// number of bits in pattern
	uint Interval;	// interval between LED changes (milliseconds)

	// variables

	bool Blinking;	// enable blinking 
	int Index;		// state (index of next output bit)

	elapsedMillis elapsed;	// elapsed time since last change
	bool TimeToBlink(){ return elapsed > Interval; }

public:

	Blinker( int pin, int pattern, int bits, uint interval ){
		Pin = pin;
		Pattern = pattern;
		Bits = bits;
		Interval = interval;
		Blinking = true;
		Index = 0;

		pinMode( pin, OUTPUT );
	}

	// control LED

	void Set( int bit ){ digitalWrite( Pin, bit ? HIGH : LOW ); }

	void On(){ Set( 1 ); }
	void Off(){ Set( 0 ); }

	// control blinking

	void Stop(){ Blinking = false; }
	virtual void Start(){ Blinking = true; Index = 0; }

	virtual void Loop(){
		if( Blinking && TimeToBlink() ){
			elapsed = 0;
			int bit = ( Pattern >> Index ) & 1;
			Index++;
			Index %= Bits;
			Set( bit );
		}
	}

	// stop and ensure specific final state

	void Shutdown( int isOn = 0 ){
		Stop();
		Set( isOn );
	}
};

