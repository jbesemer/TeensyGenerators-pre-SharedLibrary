#include "CommandParser.h"
#include "CommandProcessing.h"


// Error Reporting ////////////////////////////////////////////////////

const char* ErrorMessages[] = {
	"Unrecognized command",
	"Arg Count",
	"Bad Argument",
	"Bad Test ID",
	"Unimplemented",
	"Unrecognized name",
	"Value out of range",
	"Illegal Operation",
};

int ErrorMessageCount = sizeof( ErrorMessages ) / sizeof( ErrorMessages[ 0 ] );

void ReportError( int errNum, String extra )
{
	Serial.print( "ERR-" );
	Serial.print( errNum );
	Serial.print( " -- " );
	Serial.print( ErrorMessages[ errNum - ErrBadCommand ] );

	if( extra.length() > 0 ) {
		Serial.print( ": " );
		Serial.print( extra );
	}
	Serial.println();
}


