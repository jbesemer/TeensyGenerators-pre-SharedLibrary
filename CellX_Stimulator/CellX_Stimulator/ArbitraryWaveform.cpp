#include "ArbitraryWaveform.h"
#include "AnalogWriter.h"

// An ArbitraryWaveform is a sequence of Samples,
//	each a level of arbitrary duration

ArbitraryWaveform::ArbitraryWaveform()
{
	// Samples and Count will be initialized by subclass
}

ArbitraryWaveform::ArbitraryWaveform( int count )
{
	Samples = (Sample*)Allocate( count * sizeof( Sample ) );
	Count = count;
}

ArbitraryWaveform::ArbitraryWaveform( Sample* samples, int count )
{
	Samples = samples;
	Count = count;
}

void ArbitraryWaveform::Set( int index, ulong duration, int value ){
	if( index < Count )
		Samples[ index ].Set( duration, value );
}

void ArbitraryWaveform::Play( AnalogWriter* writer )
{
	Sample* current = Samples;
	elapsedMicros elapsed;
	ulong time = 0;

	for( int i = 0; i < Count; i++ ){
		ulong duration = current->Duration;
		uint value = current->Value;
		current++;

		writer->Write( value );

		time += duration;
		while( time > elapsed )
			continue;
	}
}

void ArbitraryWaveform::Print() {
	Serial.print( "ArbitraryWaveform " );
	Serial.println( Count );

	for( int i = 0; i < Count; i++ )
		Samples[ i ].Print();

}

