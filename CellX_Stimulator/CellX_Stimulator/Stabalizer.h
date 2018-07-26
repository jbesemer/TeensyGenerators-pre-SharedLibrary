#pragma once

#include "Config.h"

// filter out unnecessary changes to a boolean signal.

// initially the signal is false, then there are some transitions
// back and forth between true and false, until ultimately
// the signal remains steady true for a minimum interval.
// THAT is the pattern we want to recognize as a SINGLE change.

class Stabalizer {
protected:

	elapsedMillis MillisecSinceChange;	// time since last state change 
	uint Interval;			// interval defining stability, in milliseconds
	bool PreviousState;		// previous polled state, for change detection
	bool WasSet;

public:

	Stabalizer( uint milliseconds ) {
		Interval = milliseconds;
		WasSet = PreviousState = false;
	}

	bool IsStable() { return MillisecSinceChange > Interval; }

	bool HasSettled( bool changing ) {
		// remember if it was ever set
		WasSet |= changing;

		// clear timer each change
		if( PreviousState != changing ) {
			PreviousState = changing;
			MillisecSinceChange = 0;
		}

		// if it was set, but no longer, 
		// and has been stable for a while

		if( !changing && WasSet && IsStable() ) {
			WasSet = false;
			return true;
		}

		return false;
	}
};

#if false
Serial.print( "IsStable " );
Serial.print( elapsed );
Serial.print( ", " );
Serial.print( asserted );
Serial.print( ", " );
Serial.print( WasChanged );
Serial.print( ", " );
Serial.print( Interval );
Serial.print( ", " );
Serial.print( elapsed > Interval );
Serial.println();
#endif