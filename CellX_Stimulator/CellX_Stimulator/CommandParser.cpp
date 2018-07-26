#include "CommandParser.h"
#include "CommandProcessing.h"

Parser::Parser()
{
	Argv = new String[ MAX_ARGS ] ;
	Argc = 0;
	IsQuery = 0;
}

int Parser::Lookup( String name, const NameIdPair* table, const int count )
{
	for( int i = 0; i < count; i++ )
		if( name.equalsIgnoreCase( table[ i ].Name ) )
			return table[ i ].Id;

	return CmdUnrecognized;
}

int Parser::Lookup( String name )
{
	return Lookup( name, NameIds, NameIdsCount );
}

String Parser::ToString(){
	return ToString( 0 );
}

String Parser::ToString( int start ){
	String r;

	for( int i = start; i < Argc; i++ ){
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

int Parser::GetIntArg(int index) {
	if (index <Argc) 
		return Argv[index].toInt();
	
	ReportError(ErrBadArgCount, "Expected another");
	return -1;
}
