#pragma once

#include "DacOutAttenuated.h"

// forward signal levels to a DAC channel, with output signal
// optionally scaled by an arbitrary gain factor

class DacOutAttenuated : public DacOut
{
public:
	static float FixedGain;
	int FirstTime;
	float Gain;

	void SetGain( float gain ){
		Gain = gain;
		FirstTime = 1;
	}

	bool IsFixed(){ return Gain == FixedGain; }
	void Init( float gain ){ SetGain( gain ); }

	DacOutAttenuated(){ Init( FixedGain ); }
	DacOutAttenuated( float gain ){ Init( gain ); };

	virtual void Write( uint value ){
		uint dac
			= ( IsFixed())
				? value
				: (uint)( value * Gain );

		WriteDac( dac );

		if( FirstTime ){
			FirstTime = 0;
			Trace( value, dac );
		}
	}

	void Trace( uint value, uint dac ){
		Serial.print( "Gain: ");
		Serial.print( Gain );
		Serial.print( ", value: ");
		Serial.print( value );
		Serial.print( ", dac: ");
		Serial.println( dac );
	}
};
