#include "ZeroingMode.h"
#include "AnalogWriter.h"

// Blinker ZeroBlinker( ZERO_LED, 1, 2, 50 );
// ToggleButton ZeroButton( ZERO_BUTTON );

void ZeroingMode::Startup()
{
	AnalogWriter writer;

	if( !Active) {
		writer.WriteRaw( 0 );
		Serial.println( "Begin Zeroing..." );
	}

	// above test before calling base, to catch rising edge
	ToggleModeBlink::Startup();
}

void ZeroingMode::Shutdown()
{
	if(Active) {
		Serial.println( "... Done Zeroing" );
	}

	// above test before calling base, to catch falling edge
	ToggleModeBlink::Shutdown();
}

