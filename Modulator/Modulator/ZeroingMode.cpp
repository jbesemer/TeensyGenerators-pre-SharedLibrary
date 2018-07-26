#include "ZeroingMode.h"
#include "AnalogWriter.h"
#include "Button.Toggle.h"
#include "Blinker.h"

Blinker ZeroBlinker( ZERO_LED, 1, 2, 50 );
ToggleButton ZeroButton( ZERO_BUTTON );

void ZeroingMode::Loop() {
	if( ZeroButton.WasToggledOn() )
		StartZeroing();

	else if( ZeroButton.WasToggledOff() )
		StopZeroing();

	// animate the blinker, if zeroing
	if( Zeroing )
		ZeroBlinker.Loop();
}

void ZeroingMode::SetZeroing( int zeroingMode )
{
	ZeroButton.ToggleState = zeroingMode;
	if( zeroingMode )
		StartZeroing();
	else
		StopZeroing();
}

void ZeroingMode::StartZeroing()
{
	AnalogWriter writer;

	if( !Zeroing ) {
		Zeroing = 1;
		writer.WriteRaw( 0 );
		ZeroBlinker.Start();
		Serial.println( "Begin Zeroing..." );
	}
}

void ZeroingMode::StopZeroing()
{
	if( Zeroing ) {
		Zeroing = 0;
		ZeroBlinker.Shutdown();
		Serial.println( "... Done Zeroing" );
	}
}

