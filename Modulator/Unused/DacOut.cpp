#include <WProgram.h>

#include "DacOut.h"

void DacOut::Trace( int value, int dac ){
	Serial.print( "Gain: " );
	Serial.print( Gain );
	Serial.print( ", value: " );
	Serial.print( value );
	Serial.print( ", dac: " );
	Serial.println( dac );
}

const float DacOut::MAX_GAIN = 2.0;
const float DacOut::DEFAULT_GAIN = 1.0;

