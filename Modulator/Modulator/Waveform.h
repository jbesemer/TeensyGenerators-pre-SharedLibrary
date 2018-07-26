#pragma once

#include <WProgram.h>
#include "Config.h"
#include "Sample.h"
#include "AnalogWriter.h"

// Waveform is the abstract base class for all Waveforms. Waveform classes
// define a sequence of Samples, each of which is a DAC output Value,
// held for a given duration.
//
// The class hierarchy resembles the following:
//
// 	Waveform -- top level, abstract class, defining properties and methods common to all.
//	|
//	|	# Primitive Waveforms
//	|
// 	+--	ArbitraryWaveform -- waveforms defined by a sequence of Samples,
//	|	|			each a DAC Value held for a specific duration
//	|	|
//	|	+--	SquareWaveform -- outputs alternating high/low levels,
//	|	|			each of a specific duration
//	|	|
//	|	+--	ArbTestWave -- specific waveform for Jason's testing
//	|
//	+--	UniformWaveform -- waveforms defined by a sequence of DAC Values,
//	|	|			each held for the same uniform duration
//	|	|
//	|	+--	SineWaveform -- cache DAC values for a single (2pi) cycle of a sine wave.
//	|	|
//	|	+--	FixedWaveform -- a constant DAC value held for a given duration
//	|	|
//	|	+--	StairWaveform -- a starting level, followed by successive steps,
//	|				all of uniform duration
//	|
//	|	# Composite Waveforms
//	|
//	+-- Framed Waveform -- a waveform with the last sample continued so the
//	|				whole thing lasts for a given minimum overall duration
//	|
//	+-- WaveformTriggered -- wait indefinitely for a specific button to be pressed
//	|				and released before playing out a waveform.
//	|
//	+-- WaveformRepeated -- play a waveform repeatedly for a given overall duration
//	|
//	+-- WaveformSequence -- one or more waveforms to be played out in sequence.
//	|	|
//	|	+--	DemoWaveform -- waveforms played out in sequence, each for a given duration
//	|
//	+-- FixedWaveform -- constant output value maintained indefinitely
//

class Waveform
{
protected:

	int Count;	// number of samples
	void* Allocated;	// optional malloc'd block, freed in ~Waveform
	void* Allocate( int count );

	Waveform();

public:

	int GetCount(){ return Count; }

	virtual void Play( AnalogWriter* writer ) = 0;

	virtual void Shutdown(){}	// for cleanup after running a waveform

	virtual String ToString() { return "Waveform"; }

	virtual ~Waveform();
};
