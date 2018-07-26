#include "StairWaveform.h"

void StairWaveform::Init( int count, int startLevel, int stepLevel )
{
	for( int i = 0; i < count; i++ ){
		Samples[ i ] = startLevel;
		startLevel += stepLevel;
	}

	// Description for ToString()

	Description = "Stair ";
	Description.append( startLevel );
	Description.append( ", " );
	Description.append( stepLevel );
	Description.append( ", " );
	Description.append( Duration );

#if 1
	Serial.print( "StairWaveform::Init " );
	Serial.println( Description );
#endif
}


