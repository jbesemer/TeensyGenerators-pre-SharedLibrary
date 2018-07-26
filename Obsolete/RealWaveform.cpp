#pragma once

#include "RealWaveform.h"

ArbitraryWaveform* RealWaveform::ToArbitraryWaveform()
{
	return NULL;
}

#if RESIZE_REALWAVEFORMS
void RealWaveform::resize( int percent ){
	uint capacity = Capacity * percent / 100;

	RealSample* oldSamples = Samples;
	Samples = new RealSample[ capacity ];
	Capacity = capacity;

	for( int i = 0; i < Count; i++ )
		Samples[ i ].Set( oldSamples[ i ]);
}

void RealWaveform::Add( RealSample sample ){
	if( Count >= Capacity )
		resize();

//		Samples[ Count++ ] = sample;
	Samples[ Count++ ].Set( sample );
}
#endif // RESIZE_REALWAVEFORMS
