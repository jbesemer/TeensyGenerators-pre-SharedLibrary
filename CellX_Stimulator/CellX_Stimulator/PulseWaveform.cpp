#include "PulseWaveform.h"

//	PulseWaveform -- outputs a high value followed by a low value,
//		each of a specific duration.

void PulseWaveform::Init( int highValue, int lowValue, ulong highWidth, ulong lowWidth )
{
//	int count = 2;
//	Sample* samples = new Sample[ count ];

	Samples[ 0 ].Value = highValue;
	Samples[ 0 ].Duration = highWidth;
	Samples[ 1 ].Value = lowValue;
	Samples[ 1 ].Duration = lowWidth;
}

String PulseWaveform::ToString(){
	String r = "Pulse ";
	r.append( Samples[ 0 ].Value );
	r.append( ", " );
	r.append( Samples[ 1 ].Value );
	r.append( ", " );
	r.append( Samples[ 0 ].Duration );
	r.append( ", " );
	r.append( Samples[ 1 ].Duration );
	return r;
}


// example pulse and square wave signals

static uint squareAmplitude = (uint)( METER_MAX_DAC  * 0.90 );	// 2725

PulseWaveform PulseWaveform::ExamplePulseTrain( squareAmplitude, 100UL, 900 );

PulseWaveform PulseWaveform::ExampleSquareWave( squareAmplitude, 400UL, 400 );

