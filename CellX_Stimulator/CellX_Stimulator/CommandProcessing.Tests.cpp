#include "CommandProcessing.h"
#include "TestWaveform.h"
#include "WaveformPadded.h"
#include "Blinker.h"
#include "Blinker.OneShot.h"
#include "Button.h"
#include "Button.Toggle.h"
#include "Button.Repeating.h"
#include "Teensy.h"

#if TEENSY_LI

void Test9() {
	Serial.println( "Beginning test 9..." );
	Serial.println( "Turn P1 and observe..." );
	Serial.println( "Press B1 to exit..." );
	Blinker blinker( LED, ~0x1F, 10, 200 );		// distinct pattern from normal
	Button one( BUTTON1 );

	AnalogReaderScaled Frequency( P1, 100, 1000 );
	LedOn( LED1 );

	//for( int i = 0; i < 100; i++ ) {
	for( ;; ) {
		blinker.Loop();

		if( one.WasClicked() ) {
			break;
		}

		if( Frequency.Changed() ){
			Serial.println( Frequency.ToStringEx() );
		}
	}

	Serial.println( "Exiting test 9..." );
	LedOff( LED1 );
}

void Test8( Parser* commands ) {
	Serial.println( "Beginning test 8..." );
	Serial.println( "Turn P1 and observe..." );
	Serial.println( "Press B1 to exit..." );
	Blinker blinker( LED, ~0x1F, 10, 200 );		// distinct pattern from normal
	Button one( BUTTON1 );

	AnalogReaderFiltered reader( P1, 200 );	// 200 ms of stability
	LedOn( LED1 );

	//for( int i = 0; i < 100; i++ ) {
	for( ;; ){
		blinker.Loop();

		if( one.WasClicked() ) {
			break;
		}

		if( reader.Changed() )
		{
			Serial.println( reader.ToStringEx() );
		}
	}

	Serial.println( "Exiting test 8..." );
	LedOff( LED1 );
}

void Test7() {
	Serial.println( "Beginning test 7..." );
	ulong average = 0;
	Serial.println( "Click B4 to exit" );

	Blinker blinker( LED, ~0x1F, 10, 200 );		// distinct pattern from normal
	BlinkerOneShot oneShot( LED2, 1, 1, 30 );	// on briefly then off
	Blinker toggleBlinker( LED3, 1, 2, 50 );	// 20 Hz
	toggleBlinker.Stop();

	Button one( BUTTON1 );
	RepeatingButton two( BUTTON2 );
	ToggleButton three( BUTTON3 );
	Button four( BUTTON4 );

	oneShot.Start();

	elapsedMicros elapsed;	// for loop timing
	for( ;; ){
		elapsed = 0;

		toggleBlinker.Loop();
		blinker.Loop();
		oneShot.Loop();

		if( four.WasClicked() ) {
			while( !four.IsReleased() )	// WasClicked leaves button pressed which starts Zeroing when test exits
				continue;
			break;	//////////////////////////////////////// exit loop
		}

		if( one.IsPressed() ){
			// Serial.println( "B1.IsPressed" );
			LedOn( LED1 );
		}

		if( one.IsReleased() ){
			// Serial.println( "B1.IsReleased" );
			LedOff( LED1 );
		}

		if( two.WasClicked() ){
			Serial.println( "B2.WasClicked" );
			oneShot.Start();
			// b2toggle = !b2toggle;
			// LedSet( LED2, b2toggle );
		}

		// if( false && two.IsReleased() ){	// thought this would be like WasClickedOff but it isn't
		// 	Serial.println( "B2.IsReleased" );
		// 	LedOff( LED2 );
		// }

		if( three.WasToggledOn() ){
			Serial.println( "B3.WasToggledOn" );
			toggleBlinker.Start();
		}

		if( three.WasToggledOff() ){
			Serial.println( "B3.WasToggledOff" );
			toggleBlinker.Shutdown();
		}

		if( three.ToggleState ){
			toggleBlinker.Loop();
		}

		average = ( average + elapsed ) / 2;
	}
	Printf( "... Exiting test 7, average = %ld\n", average );
}

void Test5(){
	for(;;){
		int button = AnyButtonPressed();
		if( button == BUTTON_NONE )
			continue;
		Serial.print( "Button ");
		Serial.print( PORT_TO_BUTTON( button ) );
		Serial.print( ": " );
		Serial.println( ButtonPressed( button ));
		return;
	}
}

#endif // TEENSY_LI

void Test4a( int channel ){
	uint value = analogRead( channel );
	Serial.print( "A" );
	Serial.print( channel );
	Serial.print( ": " );
	Serial.println( value );
}

void Test4(){
	for( int i = 0; i < 9; i++ )
		Test4a( i );
}

void Test3(){
	AnalogWriter Writer;
	elapsedMicros elapsed = 0;

	int count = 0;
	while( elapsed < 10000000 ){
		Writer.WriteRaw( 0 );
		Writer.WriteRaw( 0xfff );
		count++;
	}

	Serial.print( "elapsed=" );
	Serial.print( elapsed );
	Serial.print( " count=" );
	Serial.println( count );
}

WaveformPadded FramedWave;

void TestCommand( Parser* commands ){
	int id
		= ( commands->Argc == 2 )
				? commands->Argv[ 1 ].toInt()
				: -1;

	switch( id ){
		default:
			ReportError( ErrBadTestId );
			break;

		case 0:
			Serial.print( "Free : " );
			Serial.println( FreeRam() );
			break;

		case 1:
			FramedWave.TheWaveform = &ArbTestWave ;
			FramedWave.Duration = 10000;
			StartWaveform( &FramedWave );
			break;

		case 2:
			FramedWave.TheWaveform = &UniTestWave ;
			FramedWave.Duration = 10000;
			StartWaveform( &FramedWave );
			break;

		case 3:
			Test3();
			break;

		case 4:
			Test4();
			break;

		case 6:
			// re-run setup for testing
			setup();
			break;

#if TEENSY_LI
		case 5:
			Test5();
			break;

		case 7:
			Test7();
			break;

		case 8:
			Test8( commands );
			break;
		case 9:
			Test9();
			break;
#endif // TEENSY_LI

	}
}


