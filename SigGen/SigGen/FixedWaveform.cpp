#include "FixedWaveform.h"
#include "Generator.h"

// A FixedWaveform is a single level output for a specific duration

FixedWaveform::FixedWaveform( int level, ulong duration )
	: Sample( level )
	, Duration( duration )
{
}

FixedWaveform::FixedWaveform( int level )
	: Sample( level )
	, Duration( DEFAULT_DURATION )
{
}

FixedWaveform::FixedWaveform()
	: Sample( 0 )
	, Duration( DEFAULT_DURATION )
{
}

void FixedWaveform::Play( AnalogWriter* writer )
{
	writer->Write( Sample );
	
	elapsedMicros elapsed;
	while( Duration > elapsed )
		continue;
}
