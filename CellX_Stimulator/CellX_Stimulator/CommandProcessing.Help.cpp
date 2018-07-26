#include "CommandProcessing.h"

void HelpCommand(){
	Serial.println( "Commands:	// Upper/Lower case doesn't matter" );
	Serial.println( "?		// help (show this list)" );
	Serial.println( "*idn?		// identify command" );
	Serial.println( "startup?	// show current startup command" );
	Serial.println( "startup ...	// save ... in EEPROM as startup command" );
	Serial.println( "factory		// restore EEPROM contents to factory defaults" );
	// Serial.println( "test n		// run test #n. see source CommandProcessing::TestCommand" );

	// CellX commands /////////////////////////////////////////////////

	// Mode commands //////////////////////////////////////////////////

	Serial.println("\nMode Commands:");
#if ENABLE_GAIN_COMMANDS
	Serial.println("gain [gain]	// set gain factor [to unity]");
	Serial.println( "gain?		// query gain factor" );
	Serial.println( "variablegain [0|1] // disable|enable variable gain" );
	Serial.println( "variablegain?	// query variable gain" );
#endif
	Serial.println( "zero [0|1]	// start/stop zeroing mode" );
	Serial.println( "demo [0|1]	// start/stop demo mode" );
	Serial.println( "stop		// stop current waveform" );
	// Serial.println( "zero // send zeros" );

	// CellX commands /////////////////////////////////////////////////

	CellX_Help();

	// Waveform commands //////////////////////////////////////////////

	Serial.println( "\nWaveform Commands:" );
	Serial.println( "pulse max,[min,]width,duration		// start pulse wave" );
	Serial.println( "sine amplitude,offset,count,width	// start sine wave" );
	Serial.println( "step count,start,step,width		// start step wave" );
	Serial.println( "fixed level				// send fixed level" );
#if TEENSY_LI
	Serial.println( "oneshot max,[min,]width			// start oneshot mode" );
#endif
#if ENABLE_GAIN_COMMANDS
	Serial.println( "varsine a1,a2, o1,o2, f1,f2, count	// start variable sine wave" );
#endif

#if ENABLE_COMMAND_MODIFIERS
	Serial.println( "\nCommand Modifiers:" );
	Serial.println( "padded duration ...	// play ... waveform padded out to duration" );
	Serial.println( "triggered button ...   // wait for button click then play ... waveform" );
	Serial.println( "repeat duration ...    // play ... waveform padded out to duration" );
#endif

#if ENABLE_DOWNLOAD_COMMANDS
	Serial.println( "\nDownload Commands:" );
	Serial.println( "def arb|uni, count [,duration]	// define uniform or arbitrary waveform" );
	Serial.println( "load [duration,] level		// add sample to current waveform" );
	Serial.println( "play		// generate downloaded waveform to DAC" );
	Serial.println( "def?		// show current waveform" );
	Serial.println( "undef		// delete current waveform" );
	Serial.println( "stats		// display stats and diagnostics about downloaded waveform" );
#endif
}

