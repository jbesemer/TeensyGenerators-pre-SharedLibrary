#include "CommandProcessing.h"

// Serial Polling, Command Parsing and Execution //////////////////////////////

// assemmble any serial data into SerialData, ignoring newlines and
// passing each CR-terminated command to InvokeCommand()

String SerialPollingData = "";

void SerialPolling() {
	while( Serial.available() ) {
		char ch = (char)Serial.read();

		if( ch == '\n' )
			continue;

		if( ch == '\r' ) {
			ParseAndExecute( SerialPollingData );
			SerialPollingData = "";
		}

		SerialPollingData += ch;
	}
}

// Command Parsing and Execution //////////////////////////////////////

void ParseAndExecute( String data ) {
#if 0
	Serial.print( "InvokeCommand: " );
	Serial.println( data );
#endif

	if( TheParser.Parse( data ) <= 0 )
		return;

	int code = TheParser.Lookup( TheParser.Argv[ 0 ] );
	InvokeCommand( code, &TheParser );
}

// For a primitive kind of synchronization, the following command methods
// rely on the fact that they run only when TheGenerator .Loop is NOT executing.
// Thus they may blithely change parameters which affect overal operation of
// the Generator and CommandProcessor themselves.

void InvokeCommand( int code, Parser* parser ) {
	switch( code ) {
	case CmdUnrecognized:
		ReportError( ErrBadCommand, parser->Argv[ 0 ] );
		return;

		// Misc commands
	case CmdIdentify:
		IdentifyCommand();
		break;
	case CmdHelp:
		HelpCommand();
		break;
	case CmdTest:
		TestCommand( parser );
		break;

	case CmdSetStartup:
	case CmdGetStartup:
		StartupCommand( parser );
		break;
	case CmdFactory:
		FactoryCommand( parser );
		break;

	case CmdStop:
		StopWaveform();
		break;
	case CmdZero:
		ZeroCommand(parser);
		break;
	case CmdDemo:
		DemoCommand(parser);
		break;

	case CmdDac:
		DacCommand(parser);
		break;
	case CmdSet:
		SetCommand(parser);
		break;
	case CmdGet:
		GetCommand(parser);
		break;

#if ENABLE_GAIN_COMMANDS
	case CmdGetGain:
	case CmdSetGain:
		GainCommand( &Commands );
		break;
#if TEENSY_LI
	case CmdGetVariableGain:
	case CmdSetVariableGain:
		VariableGainCommand( &Commands );
		break;
#endif
#endif
		// waveform commands

	case CmdSineWave:
		SineCommand( parser );
		break;
#if TEENSY_LI
	case CmdVarSineWave:
		VarSineCommand( &Commands );
		break;
	case CmdOneShot:
		OneShotCommand( &Commands );
		break;
#endif
	case CmdPulse:
		PulseCommand( parser );
		break;
	case CmdSteps:
		StepsCommand( parser );
		break;
	case CmdFixed:
		FixedCommand( parser );
		break;

		// download commands
#if ENABLE_DOWNLOAD_COMMANDS
	case CmdUndefine:
		UndefineCommand();
		break;
	case CmdDefine:
		DefineCommand( parser );
		break;
	case CmdShowDef:
		ShowDefCommand( parser );
		break;
	case CmdLoad:
		LoadCommand( parser );
		break;
	case CmdStats:
		StatsCommand( parser );
		break;
	case CmdPlay:
		PlayCommand( parser );
		break;
#endif // ENABLE_DOWNLOAD_COMMANDS

	default:
		ReportError( ErrUnimplemented, code );
		break;
	}
}
// Command Table //////////////////////////////////////////////////////



// NamedIdPair eliminates the need to constrain the order 
// of the enums and the commands in any way.
// commands with "?" must preceed the ones without a suffix

const NameIdPair NameIds[] = {
	{ CmdIdentify, "*idn?" },	// SCPI identify command
	{ CmdHelp, "?" },			// help    // TODO: make table of name, code pairs (so "help" can be synonym for "?")
	{ CmdTest, "test" },		// test command
	{ CmdGetStartup, "startup?" },	// query startup command 
	{ CmdSetStartup, "startup" },	// define startup command and put it in EEPROM
	{ CmdFactory, "factory" },	// restore EEPROM to factory defaults

	{ CmdDac, "dac" },			// set dac level
	{ CmdSet, "set" },			// set output on or off
	{ CmdGet, "get" },			// display input values

	{ CmdStop, "stop" },		// stop current waveform
	{ CmdZero, "zero" },		// start zeroing or resume previous waveform
	{ CmdDemo, "demo" },		// start or stop demo mode

	{ CmdSineWave, "sine" },	// start sine wave
	{ CmdPulse, "pulse" },		// start pulse wave
	{ CmdSteps, "step" },		// start step wave
	{ CmdFixed, "fixed" },		// start fixed level "waveform"

#if TEENSY_LI
	{ CmdOneShot, "oneshot" },	// start one-shot pulse mode
#endif
#if ENABLE_GAIN_COMMANDS
	{ CmdVarSineWave, "varsine" },	// start variable sine wave
	{ CmdGetGain, "gain?" },	// get gain factor
	{ CmdSetGain, "gain" },		// set gain factor
	{ CmdGetVariableGain, "variablegain?" },// enable/disable variable gain
	{ CmdSetVariableGain, "variablegain" },	// enable/disable variable gain
#endif
#if ENABLE_COMMAND_MODIFIERS
#endif
#if ENABLE_DOWNLOAD_COMMANDS
	{ CmdUndefine, "undef" },	// clear the custom waveform
	{ CmdDefine, "def" },		// create custom waveform
	{ CmdShowDef, "def?" },		// show custom waveform
	{ CmdLoad, "load" },		// load custom waveform
	{ CmdStats, "stats" },		// calculate and display statistics about RealWaveform
	{ CmdPlay, "play" },		// play recently defined waveform
#endif
};

int NameIdsCount = sizeof( NameIds ) / sizeof( NameIds[ 0 ] );

