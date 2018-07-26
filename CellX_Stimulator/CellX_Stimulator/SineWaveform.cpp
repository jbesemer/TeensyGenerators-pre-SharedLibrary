#include "SineWaveform.h"
#include "Generator.h"

// Initialization ////////////////////////////////////////////////////////////

// generate one cycle of sine wave divided evenly over count samples
void SineWaveform::Init( float amplitude, float offset ) {
	float delta = TWO_PI / Count;

	for( int i = 0; i < Count; i++ ) {
		float x = delta * i;
		float y = amplitude * sin( x ) + offset;
		uint v = (uint)max( 0, min( (int)y, (int)METER_MAX_DAC ) );
		Samples[ i ] = v;
	}

	Prefix = "";
	Prefix.append( amplitude );
	Prefix.append( ", " );
	Prefix.append( offset );
	Prefix.append( ", " );
	Prefix.append( Count );
	Prefix.append( ", " );
}

// generate partial cycle of sine wave divided evenly over count samples
// start and stop are the starting and ending angles in degrees of the partial sine wave
void SineWaveform::Init( float amplitude, float offset, float starting, float ending ) {
	float x0 = ( starting / 360 ) * TWO_PI;
	float x1 = ( ending / 360 ) * TWO_PI;
	float delta = ( x1 - x0 ) / Count;
	float x = x0;

	for( int i = 0; i < Count; i++ ) {
		float y = amplitude * sin( x ) + offset;
		x += delta;
		uint v = (uint)max( 0, min( (int)y, (int)METER_MAX_DAC ) );
		Samples[ i ] = v;
	}
}


void SineWaveform::SetFrequency( float frequency ) {
	if( frequency <= 0 ) {
		Serial.printf( "Set frequency cannot be <= 0" );
		return;
	}

	Duration
		= Duration_uS(
			frequency,
			Count );

	Suffix = "";
	Suffix.append( frequency );
	Suffix.append( "  # Hz (" );
	Suffix.append( Duration );
	Suffix.append( " uSec)" );
}

void SineWaveform::SetDuration( float duration ) {
	Duration = duration;

	Suffix = "";
	Suffix.append( duration );
	Suffix.append( "  # uS (" );
	Suffix.append( Frequency_Hz( duration ) );
	Suffix.append( " Hz)" );
}

// ExampleSineWave ////////////////////////////////////////////////////

static uint duration = 10;
static float sineAmplitude = (unsigned int)( METER_MAX_DAC / 2 * 0.90 );	// 1362
static float sineOffset = (unsigned int)( METER_MAX_DAC / 2 * 0.90 );		// 1362

SineWaveform SineWaveform::ExampleSineWave( sineAmplitude, sineOffset, 200, (ulong)duration );
