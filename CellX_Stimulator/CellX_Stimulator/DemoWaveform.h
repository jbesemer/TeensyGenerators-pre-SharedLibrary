#include "WaveformSequence.h"

#define DEFAULT_DEMO_INTERVAL 2000
#define DEFAULT_DEMO_GAIN 0.1

class DemoWaveform : public WaveformSequence
{
 protected:

	elapsedMillis msElapsed = 0;	 // ms timer for mode changes
	ulong Interval = DEFAULT_DEMO_INTERVAL;	// change waveform every 2 seconds

public:
	DemoWaveform( int count, ulong interval );
	DemoWaveform( Waveform** waveforms, int count, ulong interval );
	
	virtual String ToString() { return "DemoWaveform"; }
	
	virtual void Play( AnalogWriter* writer );

	static DemoWaveform* CreateDemoWaveform();
};

extern Waveform* DemoWaveforms[];

extern int DemoWaveformsCount;
