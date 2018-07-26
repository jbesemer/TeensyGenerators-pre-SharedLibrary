#include "CommandProcessing.h"
#include "CellX_Demo.h"
#include "StairWaveform.h"

const char* ModDate = "3/14/2018 2:39 PM";

int CellX_Demo_Dacs[] = {
	LTC2636_DAC_A,
	LTC2636_DAC_B,
	LTC2636_DAC_C,
	LTC2636_DAC_D,
};

// AMOD names (indices in above table)
#define AMOD1 0
#define AMOD2 1
#define AMOD3 2
#define AMOD4 3

#define LED5 13 // BLUE, same as LED

int CellX_Demo_Leds[] = {
	LED1,
	LED2,
	LED3,
	LED4,
	LED5,
};

int CellX_Demo_DacCount = sizeof( CellX_Demo_Dacs ) / sizeof( CellX_Demo_Dacs[ 0 ] );
int CellX_Demo_LedCount = sizeof( CellX_Demo_Leds ) / sizeof( CellX_Demo_Leds[ 0 ] );

const int SampleCount = 200;
const int WaveMax = 3686; // 4096 * 90%
const int StepSize = WaveMax / SampleCount;
const int OverallDuration = 200000; // uS
const int SampleDuration_us = OverallDuration / SampleCount;

StairWaveform RampUp( SampleCount, 0, StepSize, SampleDuration_us );
StairWaveform RampDown( SampleCount, WaveMax, -StepSize, SampleDuration_us );

void CellX_Demo::PlayWaveform( int index ){
	Serial.print( "play Waveform on DAC" );
	Serial.println( index + 1 );
	MuxWriter->SetAddr( CellX_Demo_Dacs[ index ] );
	RampUp.Play( MuxWriter );	// synchronous -- plays entire waveform before returning
	RampDown.Play( MuxWriter );	// synchronous -- plays entire waveform before returning
	MuxWriter->WriteRaw( 0 );	// reset to 0 when waveform is done
}

void CellX_Demo::Loop(){
	ToggleMode::Loop();

	if( Active ) {
		if( Index >= CellX_Demo_LedCount ) {
			Index = 0;
		}
		Serial.println();
		Serial.print( "CellX Demo Index " );
		Serial.println( Index );

		int ledPin = CellX_Demo_Leds[ Index ];
		LedOn( ledPin );

		if( Index >= CellX_Demo_DacCount ) {
			// special mode
			SetAllDmod( 0 );
			PlayWaveform( AMOD1 );
		}
		else {
			// regular mode
			SetDmod( Index, 1 );
			PlayWaveform( Index );
			SetDmod( Index, 0 );
		}

		LedOff( ledPin );
		Index++;
	}
}

const int StartupDelay = 3000;	// ms

void CellX_Demo::Startup(){
	// test before calling base, to catch rising edge of .Active
	if( !Active ) {
		Serial.println( "Pausing for CellX to complete initialization" );
		MainBlinker.SetPattern( 0x1, 2, 50 );			// fast blink
		elapsedMillis wait;
		while( wait < StartupDelay ){
			MainBlinker.Loop();
		}
		//MainBlinker.SetPattern( 0x15, 10, 100 );    // blinks LED thrice per sec
		//MainBlinker.SetPattern(0x1, 2, 50);
		MainBlinker.Shutdown();

		Serial.println( "Starting CellX Demo" );
		ClearAllLEDs();
		Index = CellX_Demo_LedCount - 1;	// start with last one
		// Index = 0;	// start with first one
		MuxWriter->Reset();
		SetAllDmod( 0 );
		ToggleKeyswitch();
	}

	ToggleMode::Startup();
}

void CellX_Demo::Shutdown(){
	// test before calling base, to catch falling edge of .Active
	if( Active ) {
		Serial.println( "Stopping CellX Demo" );
		MuxWriter->Reset();
		ClearAllLEDs();
		SetAllDmod( 0 );
		MainBlinker.SetPattern( 0x15, 10, 100 );    // blinks LED thrice per sec
		MainBlinker.Start();
	}

	ToggleMode::Shutdown();
}

void ClearAllLEDs() {
	for( int i = 0; i < CellX_Demo_DacCount; i++ )
		LedOff( CellX_Demo_Leds[ i ] );
}

void ToggleKeyswitch() {
	Serial.println( "Toggle KeyOn: OFF..." );
	digitalWrite( KeyOn, 0 );
	delay( 100 );
	Serial.println( "Toggle KeyOn: ON..." );
	digitalWrite( KeyOn, 1 );
}

int CellX_DMOD[] = {
	DMOD1,
	DMOD2,
	DMOD3,
	DMOD4,
};

void SetDmod( int index, int value ) {
	int dmod = CellX_DMOD[ index ];
	Serial.print( "Setting DMOD" );
	Serial.print( index + 1 );
	Serial.println( ( value ? " ON" : " OFF" ) );
	digitalWrite( dmod, value );
}

void SetAllDmod( int value ) {
	Serial.print( "Setting all DMODs " );
	Serial.println( ( value ? " ON" : " OFF" ) );
	digitalWrite( DMOD1, value );
	digitalWrite( DMOD2, value );
	digitalWrite( DMOD3, value );
	digitalWrite( DMOD4, value );
}
