#include "CommandProcessing.h"
#include "PersistentSettings.h"
#include "DemoWaveform.h"
#include "Generator.h"
#include "Button.Toggle.h"
#include "Button.h"

// CommandProcessing has two responsibilities:
//		1. it processes command input from the serial port
//		2. it drives the DemoMaker Loop, which when enabled regularly changes
//			the main generator's waveforms

CommandProcessing::CommandProcessing(){
	VariableGainEnabled = VariableGainEnabledDefault;

	TheGenerator.SetWriter( &TheAnalogWriterScaled );
}

// called from main at startup befor processing starts

void CommandProcessing::Setup(){

	// fetch settings from eeprom or restore factory defaults
	if( !Settings.LoadFromEEPROM() )
		Settings.SetFactoryDefaults();

	PrintFreeRam();

	// handle other settings first

	char* command = Settings.Settings.StartupCommand;

	// handle startup command
	Serial.print( "Invoking Startup Command = " );
	Serial.println( command );
	InvokeCommand( command );
}

// This method takes care of SerialPolling. SerialPolling occasionally recognizes
// a command and calls the corresponding method above.
//

void CommandProcessing::Loop() {
	TheZeroingMode.Loop();

	if( !IsZeroing() ) {
		MaybeAdjustGain();

		// generate one cycle of currently selected waveform
		TheGenerator.Loop();
	}

	// process any serial input
	SerialPolling();
}

// Zeroing Mode /////////////////////////////////////////////////////////////

// suspend waveform output and send continuous zero
// previous waveform resumes when Zeroing ends

void CommandProcessing::ZeroCommand( Parser* commands ) {
	int zeroMode = commands->GetSingleIntArg( 1 );	// default is ON
	TheZeroingMode.SetZeroing( zeroMode );
}


// Specific Commands //////////////////////////////////////////////////////////

// Command methods don't have to be CommandProcessing members unless they
// also need to access other CommandProcessing members.
// However non-members do have to be lexically defined before used
// (in InvokeCommand, below).

void CommandProcessing::GainCommand( Parser* commands ){
	// gain [gain]			// default 1.0; does not change VariableGain setting
	float gain;

	if( commands->IsQuery ){
		Serial.print( "Gain = " );
		Serial.println( TheAnalogWriterScaled.GetGain() );
		return;
	}

	switch( commands->Argc ){
	default:
		Parser::ReportError( ErrBadArgCount );
		return;
	case 2:
		gain = commands->Argv[ 1 ].toFloat();
		break;
	case 1:
		gain = 1.0;
		break;
	}

	TheAnalogWriterScaled.SetGain( gain );
}

#if TEENSY_LI

void CommandProcessing::VariableGainCommand( Parser* commands ){
	// variablegain [enabled]			// default ON; does not change Gain setting

	if( commands->IsQuery ){
		Serial.print( "variablegain = " );
		Serial.println( VariableGainEnabled );
		return;
	}

	bool enabled = commands->GetSingleIntArg( 1 );	// default is ON
	SetVariableGainEnabled( enabled );
}

void CommandProcessing::SetVariableGainEnabled( bool enabled ){
	VariableGainEnabled = enabled;
	LedSet( VARGAIN_LED, enabled );
}

AnalogReaderFiltered ADC( P1 );
#endif // TEENSY_LI

void CommandProcessing::MaybeAdjustGain(){
#if TEENSY_LI
	if( VariableGainEnabled ){
		if( ADC.Changed() ){
			uint adc = ADC.Current;
			float gain = ( (float)adc * MAX_GAIN ) / ADC_MAX;
			TheAnalogWriterScaled.SetGain( gain );

			Serial.print( "Adc: " );
			Serial.print( adc );
			Serial.print( ", gain: " );
			Serial.println( gain );
		}
	}
#endif // TEENSY_LI
}

void CommandProcessing::IdentifyCommand(){
	String id = "JB, Inc - ";
	id.append( ASSEMBLYNAME );
	id.append( " - v" );
	id.append( VERSION );
	id.append( " - " );
	id.append( DATE );

	Serial.println( id );
}

void CommandProcessing::StartupCommand( Parser* commands ) {

	if( !commands->IsQuery ) {
		String command = commands->Original.substring( 8 ).trim();

		if( command.length() > 0 ) {
			Serial.print( "saved new StartupCommand: \"" );
			Serial.print( command );
			Serial.println( "\"" );

			Settings.Settings.SetStartupCommand( command );
			Settings.SaveToEEPROM();
			return;
		}

		// fall through if not query but also no new startup command
	}

	// otherwise show existing
	Serial.print( "Current startup command: " );
	Serial.println( Settings.Settings.StartupCommand );
}

void CommandProcessing::FactoryCommand( Parser* commands ){
	Settings.SetFactoryDefaults();
	Settings.SaveToEEPROM();
	Serial.println( "Restored EEPROM to Factory Defaults" );
}

