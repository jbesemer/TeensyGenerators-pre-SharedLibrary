#pragma once

#include "Config.h"

// The Teensey ADC has 12 bits, but the circuit is rather noisy. That is, the readings
// vary even when the pots are not moving. Selecting fewer bits throws away the low order ones, 
// which helps reduce the noise. Even then, we had to add a filter to eliminate the jitter.
//
// also since polling ADC is for UI stuff, which is not performance critical,
// we can freely use floating point arithmetic.

#define ADC_BITS	10
#define ADC_MAX		(( 1 << ADC_BITS ) - 1 )	// 0x3ff

class AnalogReader
{
protected:
	int Pin;	// ADC pin

public:
	uint Current;	// most recent sample

	AnalogReader( int pin ) {
		analogReadResolution( ADC_BITS );
		Pin = pin;
		Current = Read();
	}

	// analogRead: 0 = full clockwise; ADC_MAX = full counterclockwise
	// Read: ADC_MAX = full clockwise, 0 = full counterclockwise

	uint Read() {
		return ( Current = ADC_MAX - analogRead( Pin ) );
	}

	virtual String ToString() {
		String r = "AnalogReader( ";
		r.append( Pin );
		r.append( " )" );
		
		return r;
	}
};

