#include "RealSample.h"

String ValidChars = "0123456789.+-e";

bool Validate( String data ){
	for( int i = 0; i < data.length(); i++ )
		if( ValidChars.indexOf( data[ i ]) < 0 ){
			Serial.print( "Invalid char in number: " );
			Serial.println( data );
			return false;
		}

	return true;
}

float Convert( String data ){
	data = data.trim();

	if( Validate( data ))
		return data.toFloat();
	else
		return 0;
}

void RealSample::Set( String data ){
	// set sample to data contained in one line of a waveform file

	const char SPACE = ' ';	// separator between name and optional args
	const char COMMA = ',';	// separator between successive args

	data.replace( COMMA, SPACE );
	int index = data.indexOf( SPACE );
	if( index <= 0 ){
		Serial.print( "missing space in: " );
		Serial.println( data );
		return;
	}

	Time = Convert( data.substring( 0, index ));
	Volts = Convert( data.substring( index + 1 ));
}

