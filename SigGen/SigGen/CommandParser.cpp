#include "CommandParser.h"

Parser::Parser()
{
	Argv = new String[ MAX_ARGS ] ;
	Argc = 0;
	IsQuery = 0;
}

int Parser::Lookup( String name )
{
	for( int i=0; i < Count; i++ )
		if( name.equalsIgnoreCase( NameIds[ i ].Name ) )
			return NameIds[ i ].Id;

	return CmdUnrecognized;
}

void Parser::ReportError( int errNum, String extra )
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

String Parser::ToString(){
	return ToString( 0 );
}

String Parser::ToString( int start ){
	String r;

	for( int i = start; i < Count; i++ ){
		r.append( Argv[ i ] );
		r.append( " " );
	}

	return r;
}

// commands syntax: <name> [space {comma-separated-arguments}]	// ala SCPI

// Argv[0] is the command name; Argv[1] the first argument, etc.
// Argc is 1 greater than the number of arguments, to account for the command name.
// four arguments are accessed via Argv[1] thru Argv[4].

int Parser::Parse( String command )
{
	command = command.replace( "\t", " " );
	Original = command;

	const char SPACE = ' ';	// separator between name and optional args
	const char COMMA = ',';	// separator between successive args
	char SEPARATOR = SPACE;	// first we split on command separator
	command = command.trim();	// ignore leading spaces
	Argc = 0;

	while( command.length() > 0 && Argc < MAX_ARGS )
	{
		int index = command.indexOf( SEPARATOR );

		if( index <= 0 ){
			Argv[ Argc++ ] = command.trim();
			break;
		}

		Argv[ Argc++ ] = command.substring( 0, index ).trim();
		command = command.substring( index + 1 ).trim();

		SEPARATOR = COMMA;	// after first we split on arg separator
	}

#if 0
	for( int i = 0; i < Argc; i++ ){
		Serial.print( "arg " );
		Serial.print( i );
		Serial.print( ": " );
		Serial.println( Argv[ i ] );
	}
#endif

	// command is query if ends with '?'

	IsQuery = ( Argc > 0 && Argv[ 0 ].endsWith( "?" ) );

	return Argc;
}

int Parser::ParseCSV( String line ){
	Argc = 0;

	while( line.length() > 0 && Argc < MAX_ARGS ){
		int index = line.indexOf( ',' );
		if( index >= 0 ){
			Argv[ Argc++ ] = line.substring( 0, index ).trim();
			line = line.substring( index + 1 );
		}
		else {
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

	IsQuery = 0; //  ( Argc > 0 && Argv[ 0 ].endsWith( "?" ) );

	return Argc;
}



// convenience functions for common arg patterns

int Parser::GetSingleIntArg( int Default ){
	if( Argc == 2 )
		return Argv[ 1 ].toInt();

	if( Argc > 2 )
		ReportError( ErrBadArgCount, "Expected single" );

	return Default;
}

// NamedIdPair eliminates the need to constrain the order 
// of the enums and the commands in any way.
// commands with "?" must preceed the ones without a suffix

const NameIdPair Parser::NameIds[] = {
	{ CmdIdentify, "*idn?" },	// SCPI identify command
	{ CmdHelp, "?" },			// help    // TODO: make table of name, code pairs (so "help" can be synonym for "?")
	{ CmdTest, "test" },		// test command
	{ CmdGetStartup, "startup?" },	// query startup command 
	{ CmdSetStartup, "startup" },	// define startup command and put it in EEPROM
	{ CmdFactory, "factory" },	// restore EEPROM to factory defaults

	{ CmdStop, "stop" },		// stop current waveform
	{ CmdZero, "zero" },		// start zeroing or resume previous waveform
	{ CmdDemo, "demo" },		// start or stop demo mode

	{ CmdSineWave, "sine" },	// start sine wave
	{ CmdPulse, "pulse" },		// start pulse wave
	{ CmdOneShot, "oneshot" },	// start one-shot pulse mode
	{ CmdSteps, "step" },		// start step wave
	{ CmdFixed, "fixed" },		// start fixed level "waveform"
	{ CmdVarSineWave, "varsine" },	// start variable sine wave

	{ CmdGetGain, "gain?" },	// get gain factor
	{ CmdSetGain, "gain" },		// set gain factor
	{ CmdGetVariableGain, "variablegain?" },// enable/disable variable gain
	{ CmdSetVariableGain, "variablegain" },	// enable/disable variable gain

	// reserved for DOWNLOAD
	{ CmdUndefine, "undef" },	// clear the custom waveform
	{ CmdDefine, "def" },		// create custom waveform
	{ CmdShowDef, "def?" },		// show custom waveform
	{ CmdLoad, "load" },		// load custom waveform
	{ CmdStats, "stats" },		// calculate and display statistics about RealWaveform
	{ CmdPlay, "play" },		// play recently defined waveform
};

int Parser::Count = sizeof( Parser::NameIds ) / sizeof( Parser::NameIds[ 0 ] );

const char* Parser::ErrorMessages[] = {
	"Unrecognized command",
	"Arg Count",
	"Bad Argument",
	"Bad Test ID",
	"Unimplemented",
	"Illegal Operation",
};

int Parser::ErrorMessageCount = sizeof( Parser::ErrorMessages ) / sizeof( Parser::ErrorMessages[ 0 ] );

