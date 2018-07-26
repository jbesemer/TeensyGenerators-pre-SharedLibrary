#include "UniformWaveform.h"
#include "Generator.h"

// A UniformWaveform is a sequence of levels of uniform duration

UniformWaveform::UniformWaveform( int count, ulong duration )
{
	Samples = (int*)Allocate( count * sizeof( int ) );
	Count = count;
	Duration = duration;

#if 0
	Serial.print( "UniformWaveform " );
	Serial.print( Count );
	Serial.print( ", " );
	Serial.println( Duration );
#endif
}

UniformWaveform::UniformWaveform( int* samples, int count, ulong duration )
{
	Samples = samples;	// Samples are "owned" by caller and will NOT be deleted by the destructor
	Count = count;
	Duration = duration;
}

void UniformWaveform::Set( int index, int value ){
	Samples[ index ] = value;
}


void UniformWaveform::Play( AnalogWriter* writer )
{
	int* current = Samples;
	elapsedMicros elapsed;
	ulong time = 0;

	for( int i = 0; i < Count; i++ ){
		uint value = *current++;

		writer->Write( value );

		time += Duration;
		while( time > elapsed )
			continue;
	}
}

void UniformWaveform::Print() {
	Serial.print( "UniformWaveform " );
	Serial.print( Count );
	Serial.print( ", " );
	Serial.println( Duration );

	for( int i = 0; i < Count; i++ )
		Serial.println( Samples[ i ] );
}
