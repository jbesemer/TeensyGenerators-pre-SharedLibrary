#include "Waveform.h"
#include "ArbitraryWaveform.h"
#include "UniformWaveform.h"
#include "CommandParser.h"

#define MAX_FIELDS 3

// helper for downloadable waveforms

class Downloader
{
protected:
	int Index;		// to track index of current waveform
	int Count;		// total number of samples

	// incoming line parsed into fields
	String* Argv;
	int Argc;

public:

	Downloader( int count ){
		Argv = new String[ MAX_FIELDS ];
		Count = count;
		Index = 0;
	}

	// true after creation until all samples have been loaded
	bool IsDownloading()	{ return Index < Count; }

};

class DownloadableArbitraryWaveform
	: public ArbitraryWaveform
{
protected:

public:
	DownloadableArbitraryWaveform( int count )
	{
	}

	virtual String ToString() { return "DownloadableArbitraryWaveform"; }
};

class DownloadableUniformWaveform
	: public UniformWaveform
{
protected:

public:
	DownloadableUniformWaveform( int count, ulong duration )
		: UniformWaveform( count, duration )
	{

	}

	virtual String ToString() { return "DownloadableUniformWaveform"; }
};
