#pragma once

#include "Config.h"

// manage stimulus to a DAC channel, with output signal
// optionally scaled by an arbitrary gain factor

class DacOut
{
public:
	static const float MAX_GAIN; // = 2.0;
	static const float DEFAULT_GAIN; //  = 1.0;

	float Gain;
	int TraceCount;

	void SetGain( float gain ){
		if( 0 < gain && gain <= MAX_GAIN )
			Gain = gain;
		else
			Serial.println( "Gain must be between 0 and 2" );
		TraceCount = 0;
	}

	DacOut() { SetGain( DEFAULT_GAIN ); }

	DacOut( float gain ) { SetGain( gain ); }

	virtual void Set( int value ){
		int dac = (int)( value * Gain );
		WriteDac( dac );

		if( TraceCount > 0 ){
			TraceCount--;
			Trace( value, dac );
		}
	}

	void Trace( int value, int dac );
};

