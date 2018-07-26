#include "Config.h"
// #include "LiTeensy.h" // included by Config.h

void LiTeensy_Setup(){
	Serial.begin( 19200 );

	pinMode( LED, OUTPUT );
	pinMode( LED1, OUTPUT );
	pinMode( LED2, OUTPUT );
	pinMode( LED3, OUTPUT );
	pinMode( LED4, OUTPUT );

	show( LED, LED1 );
	show( LED1, LED2 );
	show( LED2, LED3 );
	show( LED3, LED4 );
	show( LED4, LED );

	pinMode( BUTTON1, INPUT_PULLUP );
	pinMode( BUTTON2, INPUT_PULLUP );
	pinMode( BUTTON3, INPUT_PULLUP );
	pinMode( BUTTON4, INPUT_PULLUP );
}

// LED ports //////////////////////////////////////////////////////////////////

int LEDONTIME = 500;	// msec

void show( int pinOff, int pinOn ){
	digitalWrite( pinOff, LOW );
	digitalWrite( pinOn, HIGH );
	delay( LEDONTIME );
}

void LedSet( int ledPin, int isOn ){
	digitalWrite(
		ledPin,
		( isOn == 0 )
			? LOW
			: HIGH );
}

void LedOn( int ledPin ){
	digitalWrite( ledPin, HIGH );
}

void LedOff( int ledPin ){
	digitalWrite( ledPin, LOW );
}

// button port assignments ////////////////////////////////////////////////////

// this code assumes button shorts input pin to ground with internal pullup enabled.
// Thus button pressed means the pin is pulled LOW; else HIGH

int AllButtons[] = {
	BUTTON1,
	BUTTON2,
	BUTTON3,
	BUTTON4,
	BUTTON_NONE,
};

int AnyButtonPressed(){
	for( int i = 0; AllButtons[ i ] != BUTTON_NONE; i++ )
		if( ButtonPressed( AllButtons[ i ]))
			return AllButtons[ i ];

	return BUTTON_NONE;
}

int OppositeState( int state ){
	if( state == HIGH )
		return LOW;
	else
		return HIGH;
}

int ButtonPressed( int button ){
	return digitalRead( button ) == LOW;
}

int ButtonReleased( int button ){
	return digitalRead( button ) == HIGH;
}

// Misc. //////////////////////////////////////////////////////////////

int FreeRam ()
{
//	extern int __heap_start;
	extern int *__brkval;
	int v;
	return (int) &v - (int) __brkval;
//	return (int) &v - (__brkval == 0 ? (int) &__heap_start : (int) __brkval);
// https://learn.adafruit.com/memories-of-an-arduino/measuring-free-memory
}


// TODO: access LED and Buttons as groups:
// http://tronixstuff.com/2011/10/22/tutorial-arduino-port-manipulation/
// http://playground.arduino.cc/Learning/PortManipulation


void PrintFreeRam(){
	Serial.print( "Free ram: " );
	Serial.println( FreeRam() );
}


// Trace, Printf //////////////////////////////////////////////////////

#include <stdarg.h>

bool TraceEnabled = false;

void Trace( const char* fmt, ... ){
	if( !TraceEnabled )
		return;

	char buf[ 128 ]; // resulting string limited to 128 chars
	va_list args;
	va_start( args, fmt );
	vsnprintf( buf, 128, fmt, args );
	va_end( args );
	Serial.print( buf );
}

void Printf( const char* fmt, ... ){
	char buf[ 128 ]; // resulting string limited to 128 chars
	va_list args;
	va_start( args, fmt );
	vsnprintf( buf, 128, fmt, args );
	va_end( args );
	Serial.print( buf );
}
