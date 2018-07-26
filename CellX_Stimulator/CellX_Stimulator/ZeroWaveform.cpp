#include "ZeroWaveform.h"

void ZeroWaveform::Init()
{
	Samples[ 0 ] = 0;

#if 0
	Serial.print( "ZeroWaveform " );
	Serial.print( Count );
	Serial.print( ", " );
	Serial.println( Duration );
#endif
}

ZeroWaveform::ZeroWaveform()
	: UniformWaveform( 1, ZERO_DURATION_DEFAULT )
{
	Init();
}

ZeroWaveform::ZeroWaveform( ulong duration )
	: UniformWaveform( 1, duration )
{
	Init();
}


ZeroWaveform ZeroWaveform::Example( ZERO_DURATION_DEFAULT );

