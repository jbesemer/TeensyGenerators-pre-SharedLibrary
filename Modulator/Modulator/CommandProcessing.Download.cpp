#include "CommandProcessing.h"
#include "ArbitraryWaveform.h"
#include "UniformWaveform.h"

#if ENABLE_DOWNLOAD_COMMANDS

ArbitraryWaveform* LoadedArbWaveform = NULL;
UniformWaveform* LoadedUniWaveform = NULL;

int Index = 0;

void CommandProcessing::UndefineCommand(){	// delete previous if any 

	Stop();
	Index = 0;
	PrintFreeRam();

	if( LoadedArbWaveform != NULL ){
		delete LoadedArbWaveform;
		Serial.print( " delete arb -> " );
	}

	if( LoadedUniWaveform != NULL ){
		delete LoadedUniWaveform;
		Serial.print( " delete uni -> " );
	}

	LoadedArbWaveform = NULL;
	LoadedUniWaveform = NULL;

	PrintFreeRam();
}

// define arb[itrary]|uni[form] count [,width] 

void CommandProcessing::DefineCommand( Parser* commands ){
	ulong duration = 0;
	int count;

	switch( commands->Argc ){
	default:
		Parser::ReportError( ErrBadArgCount );
		return;
	case 4:	// duration and count
		duration = (ulong)commands->Argv[ 3 ].toInt();
		/*FALLTHROUGH*/
	case 3:	// count only
		count = commands->Argv[ 2 ].toInt();
		break;
	}

	UndefineCommand();

	String type = commands->Argv[ 1 ].toLowerCase();

	Serial.print( "defining " );
	Serial.print( type );
	Serial.print( " count=");
	Serial.print( count );
	Serial.print( " duration=" );
	Serial.println( duration );

	if( type.startsWith( "uni" ) ){
		LoadedUniWaveform = new UniformWaveform( count, duration );
	}
	else if( type.startsWith( "arb" ) ){
		LoadedArbWaveform = new ArbitraryWaveform( count );
	}
	else
	{
		Parser::ReportError( ErrBadArgument, type );
		return;
	}
}

void CommandProcessing::LoadCommand( Parser* commands ){

	// reparse command as CSV:
	// commands->ParseCSV( commands->Original );

	if( LoadedArbWaveform != NULL ){
		if( commands->Argc != 3 ){
			Parser::ReportError( ErrBadArgCount );
			return;
		}

		ulong duration = commands->Argv[ 1 ].toInt();
		int value = commands->Argv[ 2 ].toInt();
		LoadedArbWaveform->Set( Index++, duration, value );
	}

	else if( LoadedUniWaveform != NULL ){
		// we take the last field, which essentially makes 
		// the first one optional, and ignores it if present.

		if( commands->Argc < 2 ){
			Parser::ReportError( ErrBadArgCount );
			return;
		}

		int value = commands->Argv[ commands->Argc - 1 ].toInt();
		LoadedUniWaveform->Set( Index++, value );
	}

	else
		Parser::ReportError( ErrIllegal, "Load without Def" );
}

void CommandProcessing::PlayCommand( Parser* commands ){
	Stop();

	if( LoadedArbWaveform != NULL ){
		if( Index < LoadedArbWaveform->GetCount() ) {
			Parser::ReportError( ErrIllegal, "Incomplete Load" );
			return;
		}
		StartWaveform( LoadedArbWaveform );
	}

	else if( LoadedUniWaveform != NULL ){
		if( Index < LoadedUniWaveform->GetCount() ) {
			Parser::ReportError( ErrIllegal, "Incomplete Load" );
			return;
		}
		StartWaveform( LoadedUniWaveform );
	}
	else
		Parser::ReportError( ErrIllegal, "Play without Def" );
}

void CommandProcessing::ShowDefCommand( Parser* commands ) {
	int count;

	if( LoadedArbWaveform != NULL ) {
		count = LoadedArbWaveform->GetCount();
		LoadedArbWaveform->Print();
	}

	else if( LoadedUniWaveform != NULL ) {
		count = LoadedUniWaveform->GetCount();
		LoadedUniWaveform->Print();
	}

	else {
		Serial.println( "No waveforms defined" );
		return;
	}

	if( Index < count ) {
		Serial.print( "Incomplete Load: " );
		Serial.println( Index );
	}
	Serial.println();
}

void CommandProcessing::StatsCommand( Parser* commands ){
}

#endif // ENABLE_DOWNLOAD_COMMANDS