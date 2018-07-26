#pragma once

#include "AnalogReaderFiltered.h"

#define SETTLE_TIME 100	// ms

// translate DAC min..max to arbitrary float min..max range

class AnalogReaderScaled : public AnalogReaderFiltered
{
protected:
	float Min, Max;
	float Span;		// precomputed Max - Min

public:
	float Scale( uint value ) {
		return value / float( ADC_MAX )*( Max - Min ) + Min;
	}

	AnalogReaderScaled( int pin, float min, float max )
		: AnalogReaderFiltered( pin, SETTLE_TIME ), Min( min ), Max( max )
	{
		Span = Max - Min;
	}

	AnalogReaderScaled( int pin, float max )
		: AnalogReaderFiltered( pin, SETTLE_TIME ), Min( 0 ), Max( max )
	{
		Span = Max - Min;
	}

	// return current value, Scaled
	// use AnalogReaderFiltered::Changed() to know when data is ready

	float Value() { return Scale( Current ); }

	virtual String ToString() {
		String r = "AnalogReaderScaled( ";
		r.append( Pin );
		r.append( ", " );
		r.append( Min );
		r.append( ", " );
		r.append( Max );
		r.append( " )" );

		return r;
	}

	virtual String ToStringEx() {
		String r = ToString() + ": ";
		r.append( Current );
		r.append( " -> " );
		r.append( Value() );
		r.append( ", " );
		ulong ms = MillisecSinceChange;
		r.append( ms );
		r.append( ", " );
		r.append( IsStable() ? "STABLE" : "Not Stable" );

		return r;
	}
};
