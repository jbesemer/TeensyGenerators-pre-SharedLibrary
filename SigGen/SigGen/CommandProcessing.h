#pragma once

#include "Config.h"
#include "PersistentSettings.h"
#include "Generator.h"
#include "CommandParser.h"
#include "ZeroingMode.h"

#define MAX_GAIN 2.0

class CommandProcessing
{
public:
	enum { VariableGainEnabledDefault = 0 };	// http://stackoverflow.com/questions/14495536/how-to-initialize-const-member-variable-in-a-class-c

	bool IsZeroing() { return TheZeroingMode.IsZeroing(); }

protected:

	PersistentSettings Settings;
	ZeroingMode TheZeroingMode;
	Generator TheGenerator;	// generator for sending waveforms to the DAC
	Parser Commands;

	AnalogWriter TheAnalogWriter;
	AnalogWriterScaled TheAnalogWriterScaled;

	Waveform* CustomWaveform = NULL;
	void StartNewWaveform( Waveform* waveform );
	void StartWaveform( Waveform* waveform );

	String SerialData = "";
	void InvokeCommand( String data );
	void SerialPolling();

	void MaybeAdjustGain();
	bool VariableGainEnabled = 0;
	uint PrevAdc = 0;

	// commands

	void IdentifyCommand();
	void HelpCommand();

	void StartupCommand( Parser* commands );
	void FactoryCommand( Parser* commands );

	void DemoCommand( Parser* commands );
	void FixedCommand( Parser* commands );

	void StepsCommand( Parser* commands );
	void SineCommand( Parser* commands );
	void PulseCommand( Parser* commands );
	void OneShotCommand( Parser* commands );
	void ZeroCommand( Parser* commands );

#if TEENSY_LI
	void VarSineCommand( Parser* commands );
	void SetVariableGainEnabled( bool enabled );
	void VariableGainCommand( Parser* commands );
#endif

	void GainCommand( Parser* commands );
	void TestCommand( Parser* commands );

#if ENABLE_DOWNLOAD_COMMANDS
	bool Download();
	bool DownloadLine( String data );
	bool IsDownloading;

	void UndefineCommand();
	void DefineCommand( Parser* commands );
	void ShowDefCommand( Parser* commands );
	void LoadCommand( Parser* commands );
	void StatsCommand( Parser* commands );
	void PlayCommand( Parser* commands );
#endif

public:

	CommandProcessing();

	void StartDemo( int demoMode );
	void StartDemo();
	void Stop();

	void Setup(); //  PersistentSettings* settings );
	void Loop();
};

