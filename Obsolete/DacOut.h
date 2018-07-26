#pragma once

#include <WProgram.h>
#include "Config.h"

#define DAC_PIN A14

#define DAC_BITS 12
#define DAC_MAX 4095
#define DAC_MAX_VOLTS 3.5 	// supply rail = output for DAC_MAX

#define METER_MAX_VOLTS 2.2	// 200 W on Heisenberg
// different max for Meterless

#define VOLTS_TO_BITS( VOLTS ) ((uint)( DAC_MAX * VOLTS / DAC_MAX_VOLTS ))
#define METER_MAX VOLTS_TO_BITS( METER_MAX_VOLTS )

// manage stimulus to a DAC channel, with output signal limited by the
// capability of a Heisenberg dummy sensor (2.2v / 200W)

class DacOut
{
public:
	static uint Max;
	static uint MaxBits;
	static float MaxVolts;
	static float MeterMaxVolts;
	static uint MeterMax;

	int Bits;

	DacOut(){
		analogWriteResolution( DAC_BITS );	// if this function is undefined, you probably have the wrong device selected in your tool chain
		analogReadResolution( DAC_BITS );
	};

	virtual void Write( uint value ){
		analogWrite( DAC_PIN, value );
	}

	virtual float GetGain() { return 1.0; }

};

