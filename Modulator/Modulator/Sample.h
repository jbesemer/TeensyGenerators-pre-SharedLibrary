#pragma once

#include <WProgram.h>

#include "Config.h"

class Sample
{
public:
	ulong Duration;	// signal duration, micro seconds, 32 bits

	int Value;		// value, dac counts, 16-bit

	Sample(){
	}

	Sample( ulong duration, int value ){
		Set( duration, value );
	};

	void Set( ulong duration, int value ){
		Value = value;
		Duration = duration;
	};

	void Get( ulong* duration, int* value ){
		*value = Value;
		*duration = Duration;
	};

	void Print() {
		Serial.print( Duration );
		Serial.print( ", " );
		Serial.println( Value );
	}
};

#if 0
class Sample16 : public Sample
{
public:
	uint Duration;		// signal duration, micro seconds, 16 bits

	ulong GetWidth(){ return (ulong)Duration; }

	Sample16(){
	}

	Sample16( uint value, ulong duration ){
		Set( value, duration );
	};

	void Set( int value, ulong duration ){
		Value = value;
		Duration = (uint)duration;
	};

	void Get( int* value, ulong* duration ){
		*value = Value;
		*duration = (ulong)Duration;
	};
};
#endif
