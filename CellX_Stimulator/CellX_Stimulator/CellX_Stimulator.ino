/*
 Name:		CellX_Stimulator.ino
 Created:	6/23/2017 4:11:00 PM
 Modified:	3/14/2018 2:39 PM
 Author:	BesemerJ
*/

#include "CommandProcessing.h"


// Principal Objects //////////////////////////////////////////////////////////


PersistentSettings Settings;
Parser TheParser;			// input commands, parsed

Blinker MainBlinker( LED, 0x15, 10, 100 );    // blinks LED thrice per sec

AnalogWriter TheAnalogWriter;	// analog writer for waveforms
AnalogWriterScaled TheAnalogWriterScaled;	// for dynamically scaled waverorms
Generator TheGenerator(&TheAnalogWriter);		// Generate waveforms to DAC
// ZeroingMode TheZeroingMode(ZERO_BUTTON, ZERO_LED);
QuadMux TheMux(SCK, nSPICS);
AnalogWriterMux TheMuxWriter(&TheMux);
CellX_Demo TheCellX_Demo(&TheMuxWriter, ZERO_BUTTON);

// Setup //////////////////////////////////////////////////////////////////////

void setup() {
	TeensyCellX_Setup();
	Serial.println( "Starting..." );

	// fetch settings from eeprom or restore factory defaults
	if (!Settings.LoadFromEEPROM())
		Settings.SetFactoryDefaults();

	PrintFreeRam();

	IdentifyCommand();

	// handle other settings first
#if false
	char* command = Settings.Settings.StartupCommand;

	// handle startup command
	Serial.print( "Invoking Startup Command = " );
	Serial.println( command );
	InvokeCommand( command );
#endif

	// in settingactive, demo runs 1 cycle before returning
	TheCellX_Demo.SetActive( 1 );
}

// Loop ///////////////////////////////////////////////////////////////////////

// this main loop has two responsibilities:
//		1. it processes command input from the serial port
//		2. it drives the DemoMaker Loop, which when enabled regularly changes
//			the main generator's waveforms


void loop(){
	// animate LED
	MainBlinker.Loop();

	// TheZeroingMode.Loop();
	TheCellX_Demo.Loop();

#if false
	if( !TheZeroingMode.IsActive() )
	{
		MaybeAdjustGain();

		// generate one cycle of currently selected waveform
		TheGenerator.Loop();
	}
#endif

	// commands sent on serial port don't get processed until
	// after first Demo cycle

	// process any serial input
	SerialPolling();
}
