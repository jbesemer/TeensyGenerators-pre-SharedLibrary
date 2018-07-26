#include "DownloadableWaveform.h"

// DownloadableArbitraryWaveform methods

#if 0
void DownloadableArbitraryWaveform::Add(){
	if( Argc != 2 ){
		Parser::ReportError( ErrBadArgCount );
		return;
	}

	ulong duration = Argv[ 0 ].toInt();
	int value = Argv[ 1 ].toInt();
	Add( duration, value );
}

void DownloadableArbitraryWaveform::Set( int index, ulong duration, int value ){
	if( index < Count )
		Samples[ index ].Set( duration, value );
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
}

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

