#include "CommandProcessing.h"
#include "SquareWaveform.h"
#include "SineWaveform.h"

#if ENABLE_DOWNLOAD_COMMANDS

bool CommandProcessing::Create( int count ){
	// invalid count => nothing changes
	if( count <= 0 ){
		Parser::ReportError( ErrBadArgument );
		return false;
	}

	Serial.print( "Free ram: " );
	Serial.print( FreeRam() );

	// valid count => delete previous if any and create new one
	if( LoadedWaveform != NULL ){
		delete LoadedWaveform ;

		Serial.print( " delete -> " );
		Serial.print( FreeRam() );
	}

	LoadedWaveform = new RealWaveform( count );

	Serial.print( " -> " );
	Serial.print( FreeRam() );

	return true;
}

bool CommandProcessing::CreateCommand( Parser* commands ){
	if( commands->Argc != 2 ){
		Parser::ReportError( ErrBadArgCount );
		return false;
	}

	int count = commands->Argv[ 1 ].toInt();
	return Create( count );
}

void CommandProcessing::LoadCommand( Parser* commands ){
	if( !CreateCommand( commands ))
		return;

	// loading takes over the serial port for the duration, thus suspending all other activity

	if( !Download()){
		// download failed; no further action is possible; errors are announced by Download method
		delete LoadedWaveform ;
		LoadedWaveform = NULL;
	}
}

static bool IsDownloading;
static int Count;
static int Index;

bool CommandProcessing::Download()
{
	// takes over serial port for duration of download, thereby suspending most other activity
	// errors generally are fatal

	Count = LoadedWaveform->Count;
	Index = 0;
	String data;
	IsDownloading = true;

	while( IsDownloading ){
		while( Serial.available()){
			char ch = (char)Serial.read();

			if( ch == '\n' )
				continue;

			if( ch == '\r' ){
				DownloadLine( data );
				data = "";
			}

			data += ch;
		}
	}
}

bool CommandProcessing::DownloadLine( String data ){
	Serial.print( "Real: " );
	Serial.println( data );
	// Samples[ Index ].Set( data );
	IsDownloading = ( Index++ < Count - 1 );
	return true;
}


void CommandProcessing::StatsCommand( Parser* commands ){
}

void CommandProcessing::PlayCommand( Parser* commands ){
	if( LoadedWaveform != NULL )
		StartNewWaveform( LoadedWaveform->ToArbitraryWaveform());
}

#endif // ENABLE_DOWNLOAD_COMMANDS