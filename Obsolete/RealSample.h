#pragma once

#include "Config.h"

class RealSample
{
public:
	float Time;		// time of change, micro seconds from start
	float Volts;		// output level, volts

	RealSample(){
		Set( 0, 0 );
	}

	RealSample( float time, float volts ){
		Set( time, volts );
	};

	void Set( float time, float volts ){
		Time = time;
		Volts = volts;
	};

	void Set( RealSample sample ){
		Set( sample.Time, sample.Volts );
	}

	void Set( String line );
};
