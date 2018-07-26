#include "TestWaveform.h"

ulong duration = 20;

Sample ArbSamples[]={
	{ duration * 1, VOLTS_TO_DAC( 0.0625 ) },
	{ duration * 1, VOLTS_TO_DAC( 1.1 ) },
	{ duration * 2, VOLTS_TO_DAC( 1.0 ) },
	{ duration * 4, VOLTS_TO_DAC( 0.5 ) },
	{ duration * 8, VOLTS_TO_DAC( 0.25 ) },
	{ duration * 16, VOLTS_TO_DAC( 0.125 ) },
	{ duration * 32, VOLTS_TO_DAC( 0.0625 ) },
};

int ArbSampleCount = sizeof( ArbSamples ) / sizeof( ArbSamples[ 0 ]);

ArbitraryWaveform ArbTestWave( ArbSamples, ArbSampleCount );

int UniSamples[]={
	500,
	1000,
	1500,
	2000,
	2500,
};

int UniSampleCount = sizeof( UniSamples ) / sizeof( UniSamples[ 0 ]);

ulong UniSampleInterval = 500;	// uSec

UniformWaveform UniTestWave( UniSamples, UniSampleCount, UniSampleInterval );
