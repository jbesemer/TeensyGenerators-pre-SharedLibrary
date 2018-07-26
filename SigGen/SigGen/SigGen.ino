/*
 Name:		SigGen.ino
 Created:	5/21/2015 11:45:44 AM
 Author:	besemerj
*/

#include "Config.h"
#include "CommandProcessing.h"
#include "PersistentSettings.h"
#include "Blinker.h"
#include <EEPROM.h>

// Burn-down list:
//
//	Test/Debug:
//		LpemWaveform
//
//		ArbTestWave			# download? not implemented
//		StairWaveform
//		WaveformPadded
//		WaveformRepeated
//
//	Eventually:
//		need separate header/payload for PersistentSettings
//		Finish incorporating Gain and VarGain to PersistentSettings
//		special syntax for Waveform modifiers
//		convert all files to pro-forma boilerplate
//		utilize Parser.Query property to eliminate need for separate set/get "names"
//			one name => one command/function with get/set functionality
//		system of blinky lights to indicate errors

// Principal Objects //////////////////////////////////////////////////////////

// blinks LED twice every sec
Blinker blinker( LED, 0x5, 10, 100 );

// processes commands, possibly affecting waveform generation
CommandProcessing CommandProcessor; //  ( &TheGenerator );

// Setup //////////////////////////////////////////////////////////////////////

void setup() {
	Teensy_Setup();
	Serial.println( "Starting..." );

	CommandProcessor.Setup();
}

// Loop ///////////////////////////////////////////////////////////////////////

void loop(){
	// animate LED
	blinker.Loop();

	// process any commands from Serial port
	CommandProcessor.Loop();
}
