#pragma once

#include "Config.h"
#include "PrintfAndTrace.h"

// blink out a pattern once each time Start is called

// you need at least 2 bits for a pattern to be shown

class BlinkerOneShot : public Blinker
{
public:
	BlinkerOneShot( int pin, int pattern, int bits, int interval )
		: Blinker( pin, pattern, bits, interval )
	{
		Blinking = false;
	}

	virtual void Start(){ 
		Trace( "Starting %d,%d,%d", Pattern, Bits, Interval );
		Blinker::Start(); 
	}

	virtual void Loop(){
		if( Blinking && TimeToBlink() ){
			if( Index > Bits ){
				Shutdown();
			}

			elapsed = 0;
			int bit = ( Pattern >> Index ) & 1;
			Trace( "Blinking %d, %d", Index, bit );
			Index++;
			Set( bit );

		}
	}
};
