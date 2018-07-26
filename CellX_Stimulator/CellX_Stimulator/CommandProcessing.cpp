#include "CommandProcessing.h"
#include "DemoWaveform.h"
#include "Generator.h"
#include "Button.Toggle.h"
#include "Button.h"

// Universal Commands /////////////////////////////////////////////////

// Zeroing Mode ///////////////////////////////////////////////////////

// suspend waveform output and send continuous zero
// previous waveform resumes when Zeroing ends

void ZeroCommand( Parser* commands ) {
	//int zeroMode = commands->GetSingleIntArg( 1 );	// default is ON
	//TheZeroingMode.SetZeroing( zeroMode );
}


// Identify (*idn?) ///////////////////////////////////////////////////

void IdentifyCommand() {
	String id = APPNAME;
	id.append(" v");
	id.append(VERSION);
	id.append(" ");
	id.append(MODEL);
	id.append(" ");
	id.append(AUTHOR);
	id.append(" ");
	id.append(DATE);

	Serial.println(id);
}

// Startup ////////////////////////////////////////////////////////////

void StartupCommand( Parser* commands ) {

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

// Factory ////////////////////////////////////////////////////////////

void FactoryCommand( Parser* commands ){
	Settings.SetFactoryDefaults();
	Settings.SaveToEEPROM();
	Serial.println( "Restored EEPROM to Factory Defaults" );
}

// Demo Mode / Waveforms //////////////////////////////////////////////////////

void DemoCommand( Parser* commands ){
	// demo [stop if 0]

	int demoMode = commands->GetSingleIntArg( 1 );	// default is ON
	StartDemo( demoMode );
}

