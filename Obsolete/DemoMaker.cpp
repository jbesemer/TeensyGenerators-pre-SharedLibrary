#include "DemoMaker.h"
#include "SquareWaveform.h"
#include "SineWaveform.h"
#include "Generator.h"

// array of example generators

Waveform* DemoMaker::Waveforms[] = {
	&SquareWaveform::ExamplePulseTrain,
	&SquareWaveform::ExampleSquareWave,
	&SineWaveform::ExampleSineWave,
};

int DemoMaker::Count = sizeof( Waveforms ) / sizeof( Waveforms[ 0 ]);

DemoMaker::DemoMaker()
{
	Index = 0;
	IsRunning = false;	// true
}

void DemoMaker::Loop( Generator* generator )
{
	if( IsRunning
	&& msElapsed > generatorTime
	&& generator != NULL ){
		msElapsed = 0;
		Index = ( Index + 1 ) % Count;
		Waveform* waveform = Waveforms[ Index ];
		generator->Set( waveform );
		Serial.print( "Starting " );
		Serial.println( waveform->ToString() );
	}
}


