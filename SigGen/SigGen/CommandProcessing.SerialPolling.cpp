#include "CommandProcessing.h"

// Serial Polling, Command Parsing and Execution //////////////////////////////

// assemmble any serial data into SerialData, ignoring newlines and
// passing each CR-separated command to OnReceiveLine()

void CommandProcessing::SerialPolling() {
	while( Serial.available() ) {
		char ch = (char)Serial.read();

		if( ch == '\n' )
			continue;

		if( ch == '\r' ) {
			InvokeCommand( SerialData );
			SerialData = "";
		}

		SerialData += ch;
	}
}

void CommandProcessing::InvokeCommand( String data ) {
#if 0
	Serial.print( "InvokeCommand: " );
	Serial.println( data );
#endif

	if( Commands.Parse( data ) <= 0 )
		return;

	int index = Commands.Lookup( Commands.Argv[ 0 ] );

	// For a primitive kind of synchronization, the following command methods
	// rely on the fact that they run only when TheGenerator .Loop is NOT executing.
	// Thus they may blithely change parameters which affect overal operation of
	// the Generator and CommandProcessor themselves.

	switch( index ) {
	case CmdUnrecognized:
		Parser::ReportError( ErrBadCommand, Commands.Argv[ 0 ] );
		return;

		// Misc commands
	case CmdIdentify:
		IdentifyCommand();
		break;
	case CmdHelp:
		HelpCommand();
		break;
	case CmdTest:
		TestCommand( &Commands );
		break;

	case CmdSetStartup:
	case CmdGetStartup:
		StartupCommand( &Commands );
		break;
	case CmdFactory:
		FactoryCommand( &Commands );
		break;

	case CmdStop:
		Stop();
		break;
	case CmdZero:
		ZeroCommand( &Commands );
		break;
	case CmdDemo:
		DemoCommand( &Commands );
		break;

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
		// waveform commands

	case CmdSineWave:
		SineCommand( &Commands );
		break;
#if TEENSY_LI
	case CmdVarSineWave:
		VarSineCommand( &Commands );
		break;
#endif
	case CmdPulse:
		PulseCommand( &Commands );
		break;
	case CmdOneShot:
		OneShotCommand( &Commands );
		break;
	case CmdSteps:
		StepsCommand( &Commands );
		break;
	case CmdFixed:
		FixedCommand( &Commands );
		break;

		// download commands
#if ENABLE_DOWNLOAD_COMMANDS
	case CmdUndefine:
		UndefineCommand();
		break;
	case CmdDefine:
		DefineCommand( &Commands );
		break;
	case CmdShowDef:
		ShowDefCommand( &Commands );
		break;
	case CmdLoad:
		LoadCommand( &Commands );
		break;
	case CmdStats:
		StatsCommand( &Commands );
		break;
	case CmdPlay:
		PlayCommand( &Commands );
		break;
#endif // ENABLE_DOWNLOAD_COMMANDS

	default:
		Parser::ReportError( ErrUnimplemented, data );
		break;
	}
}
