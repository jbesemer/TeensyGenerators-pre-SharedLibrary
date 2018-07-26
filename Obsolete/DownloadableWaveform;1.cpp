#include "DownloadableWaveform.h"

// Downloadable methods

void Downloadable::Add( String line ){
	Parse( line );
	Add();
}

void Downloadable::Parse( String line ){
	Argc = 0;

	while( line.length() > 0 && Argc < MAX_FIELDS ){
		int index = line.indexOf( ',' );
		if( index >= 0 ){
			Argv[ Argc++ ] = line.substring( 0, index ).trim();
			line = line.substring( index + 1 );
		} else {
			Argv[ Argc++ ] = line.trim();
			break;
		}
	}

#if 1
	for( int i = 0; i < Argc; i++ ){
		Serial.print( "arg " );
		Serial.print( i );
		Serial.print( ": " );
		Serial.println( Argv[ i ] );
	}
#endif
}

// DownloadableArbitraryWaveform methods

void DownloadableArbitraryWaveform::Add(){
	if( Argc != 2 ){
		Parser::ReportError( ErrBadArgCount );
		return;
	}

	ulong duration = Argv[ 0 ].toInt();
	int value = Argv[ 1 ].toInt();
	Add( duration, value );
}

void DownloadableArbitraryWaveform::Add( ulong duration, int value ){
	if( Index < Count )
		Samples[ Index++ ].Set( duration, value );
	IsDownloading = Index < Count;
}

// DownloadableUniformWaveform methods

void DownloadableUniformWaveform::Add(){
	// we take the last field, which essentially makes 
	// the first one optional, and ignores it if present.

	if( Argc < 1 ){
		Parser::ReportError( ErrBadArgCount );
		return;
	}

	int value = Argv[ Argc - 1 ].toInt();
	Add( value );
}

void DownloadableUniformWaveform::Add( int value ){
	if( Index < Count )
		Samples[ Index++ ] = value;
	IsDownloading = Index < Count;
}

#if 0
bool isNumeric( char ch ){

	switch( ch ){
	case '+':
	case '-':
	case '.':
		//	case 'e':	// if allow scientific
		return true;
	}

	return isdigit( ch );
}
#endif

