#include "SineWaveform.h"
#include "Generator.h"

// Constructors ///////////////////////////////////////////////////////

// this method merely allocates space for a waveform; 
// duration and actual data must be supplied by caller

SineWaveform::SineWaveform( int count )
	: UniformWaveform( count, 100 )
{
}

// The signatures of the next two constructors are subtlely different,
// only differing in the type of the last parameter. Off hand, I'm not sure
// if a integer literal is supplied, which method would be chosen. 
// Use the optional L or F suffix to disambiguate.

SineWaveform::SineWaveform( float amplitude, float offset, int count, ulong duration )
	: UniformWaveform( count, duration )
{
	Init( amplitude, offset );
	SetDuration( duration );
}

SineWaveform::SineWaveform( float amplitude, float offset, int count, float hertz )
	: UniformWaveform( count, Duration_uS( hertz, count ) )
{
	Init( amplitude, offset );
	SetFrequency( hertz );
}

// Helpers ////////////////////////////////////////////////////////////

void SineWaveform::Init( float amplitude, float offset ) {
	// generate one cycle of sine wave divided evenly over count samples
	float twopi = 3.14159 * 2;
	float delta = twopi / Count;

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
