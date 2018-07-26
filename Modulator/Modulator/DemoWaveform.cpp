// 
// 
// 

#include "DemoWaveform.h"
#include "PulseWaveform.h"
#include "SineWaveform.h"
#include "AnalogWriter.h"

// array of example generators

Waveform* DemoWaveforms[] = {
	&PulseWaveform::ExamplePulseTrain,
	&PulseWaveform::ExampleSquareWave,
	&SineWaveform::ExampleSineWave,
};

// int DefaultDemoInterval = DEFAULT_DEMO_INTERVAL;		// uS

int DemoWaveformCount = sizeof( DemoWaveforms ) / sizeof( DemoWaveforms[ 0 ] );

DemoWaveform* DemoWaveform::CreateDemoWaveform(){
	return
		new DemoWaveform(
			DemoWaveforms,
			DemoWaveformCount,
			DEFAULT_DEMO_INTERVAL );
}

// Constructors 

DemoWaveform::DemoWaveform( int count, ulong interval )
	: WaveformSequence( count )
	, Interval( interval )
{
}

DemoWaveform::DemoWaveform( Waveform** waveforms, int count, ulong interval )
	: WaveformSequence( waveforms, count )
	, Interval( interval )
{
}

void DemoWaveform::Play( AnalogWriter* writer )
{
	// select waveform and advance index

	if( Index >= Count )
		Index = 0;

	// play out current waveform once

	Waveforms[ Index ]->Play( writer );

	// see if it's time to advance to next waveform

	if( msElapsed > Interval ){
		msElapsed = 0;
		Index = ( Index + 1 ) % Count;
		Serial.print( "Starting " );
		Serial.println( Waveforms[ Index ]->ToString() );
	}

	// if it's NOT time we'll play out this same waveform next time
}

