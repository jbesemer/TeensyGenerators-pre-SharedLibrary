#pragma once

#include "Config.h"
#include "RealSample.h"
#include "ArbitraryWaveform.h"

class RealWaveform
{
public:
	RealSample* Samples;
	uint Count;

	RealWaveform( uint count ){
		Count = count;
		Samples = new RealSample[ Count  ];
	};

	~RealWaveform(){
		delete Samples;
	};

	ArbitraryWaveform* ToArbitraryWaveform();

#if RESIZE_REALWAVEFORMS
	void resize(){ resize( 10 ); }
	void resize( int percent );
	void Add( RealSample sample );
#endif
};
