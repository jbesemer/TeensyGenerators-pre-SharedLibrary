#pragma once

#include "Config.h"

// The Teensey DAC is on A14, has 12 bits, and we want them all

#define DAC_PIN		A14

#define DAC_BITS	12
#define DAC_MAX		0xFFF		// (( 1 << DAC_BITS ) - 1 )

#define DAC_MAX_VOLTS	3.3 	// supply rail = output for DAC_MAX
#define METER_MAX_VOLTS	2.44	// ~200 W on Heisenberg	( there's a different max for Meterless)

#define VOLTS_TO_DAC( VOLTS )	((uint)( DAC_MAX * VOLTS / DAC_MAX_VOLTS ))
#define METER_MAX_DAC			VOLTS_TO_DAC( METER_MAX_VOLTS )

#define UNITY_GAIN 1.0

class AnalogWriter
{
protected:
	int Pin;

public:
	AnalogWriter( int pin = DAC_PIN ) {
		analogWriteResolution( DAC_BITS );
		Pin = pin;
	}

	// for speed, if you know all values are in range, 
	// or don't care if they're truncated
	
	virtual void WriteRaw( uint value ) { analogWrite( Pin, value ); }

	// keep outputs within limits

	virtual void Write( uint value ) {
		if( value < 0 )
			value = 0;
		else if( value > DAC_MAX )
			value = DAC_MAX;

		WriteRaw( value );
	}
};

// apply gain and offset to each outgoing sample

class AnalogWriterScaled : public AnalogWriter
{
public:
	float Gain;
	int Offset;

	float GetGain() { return Gain; }
	void SetGain( float gain ) { Gain = gain; }

	void Clear() {
		Gain = UNITY_GAIN;
		Offset = 0;
	}

	AnalogWriterScaled( float gain = UNITY_GAIN, int offset = 0, int pin = DAC_PIN ) : AnalogWriter( pin ) {
		Gain = gain;
		Offset = offset;
	}

	virtual void Write( uint value ) {
		value *= Gain;
		AnalogWriter::Write( value + Offset );
	}
};
