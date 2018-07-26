#include "Waveform.h"
#include "ArbitraryWaveform.h"
#include "UniformWaveform.h"
#include "CommandParser.h"

#define MAX_FIELDS 3

// mix-in for downloadable waveforms

class Downloadable 
{
protected:
	int Index;		// to track index of current waveform

	// incoming line parsed into fields
	String* Argv;
	int Argc;

	// constuctor only for subclasses
	Downloadable(){
		Argv = new String[ MAX_FIELDS ];
		Index = 0;
		IsDownloading = true;
	}

public:

	// true after creation until all samples have been loaded
	bool IsDownloading;	// { Index < Count; }

	// add downloaded line
	void Add( String line );

	// parse it into Argv/Argc fields
	void Parse( String line );

	// pass parsed line to subclass
	virtual void Add() = 0;
};

class DownloadableArbitraryWaveform
	: public ArbitraryWaveform
	, public Downloadable
{
protected:
	void Add( ulong duration, int value );

public:
	DownloadableArbitraryWaveform( int count )
		: ArbitraryWaveform( count )
	{

	}

	virtual void Add();

	virtual String ToString() { return "DownloadableArbitraryWaveform"; }
};

class DownloadableUniformWaveform
	: public UniformWaveform
	, public Downloadable
{
protected:
	void Add( int value );

public:
	DownloadableUniformWaveform( int count, ulong duration )
		: UniformWaveform( count, duration )
	{

	}

	virtual void Add();

	virtual String ToString() { return "DownloadableUniformWaveform"; }
};
