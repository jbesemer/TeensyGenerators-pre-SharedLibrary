#pragma once

#include "Config.h"
#include "PersistentSettings.h"
#include "CommandParser.h"
#include "Waveform.h"
#include "Generator.h"
#include "ZeroingMode.h"
#include "Blinker.h"
#include "QuadMux.h"
#include "AnalogWriterMux.h"
#include "CellX_Demo.h"
#include "ZeroingMode.h"
#include "Blinker.h"

#define MAX_GAIN 2.0

// command codes //////////////////////////////////////////////////////

enum CommandCode {
	CmdUnrecognized = -1,

	CmdIdentify = 0,
	CmdHelp,
	CmdTest,
	CmdGetStartup,
	CmdSetStartup,
	CmdFactory,

	CmdStop,
	CmdZero,
	CmdDemo,

	CmdSineWave,
	CmdPulse,
	CmdOneShot,
	CmdSteps,
	CmdFixed,

	CmdDac,
	CmdSet,
	CmdGet,

#if ENABLE_GAIN_COMMANDS
	CmdGetGain,
	CmdSetGain,
	CmdGetVariableGain,
	CmdSetVariableGain,
#endif
#if ENABLE_COMMAND_MODIFIERS
#endif
#if ENABLE_DOWNLOAD_COMMANDS
	CmdUndefine,
	CmdDefine,
	CmdShowDef,
	CmdLoad,
	CmdStats,
	CmdPlay,
#endif
};

// Principal Objects //////////////////////////////////////////////////

extern Blinker MainBlinker;
extern PersistentSettings Settings;
//extern ZeroingMode TheZeroingMode;
extern Generator TheGenerator;		// Generate waveforms to DAC
extern Parser TheParser;			// input commands, parsed
extern AnalogWriter TheAnalogWriter;	// analog writer for waveforms
extern AnalogWriterScaled TheAnalogWriterScaled;	// for dyncamically scaled waverorms
extern QuadMux TheMux;
extern AnalogWriterMux TheMuxWriter;

extern CellX_Demo TheCellX_Demo;
extern void CellX_Help();

// Commands and related ///////////////////////////////////////////////

extern void SerialPolling();
extern void ParseAndExecute( String data );
extern void InvokeCommand( int code, Parser* parser );

extern Waveform* CustomWaveform;
extern void StartNewWaveform( Waveform* waveform );
extern void StartWaveform( Waveform* waveform );
extern void StopWaveform();

extern void DemoCommand( Parser* commands );
extern void StartDemo( int demoMode );
extern void StartDemo();

extern void IdentifyCommand();
extern void HelpCommand();
extern void StartupCommand( Parser* commands );
extern void FactoryCommand( Parser* commands );

extern void ZeroCommand( Parser* commands );
extern void TestCommand( Parser* commands );

extern void StepsCommand( Parser* commands );
extern void SineCommand( Parser* commands );
extern void PulseCommand( Parser* commands );
extern void FixedCommand( Parser* commands );
#if TEENSY_LI
extern void OneShotCommand( Parser* commands );
#endif

extern void DacCommand( Parser* commands );
extern void SetCommand( Parser* commands );
extern void GetCommand( Parser* commands );
extern void ShowPin( String name, int port );
extern void ShowPin( String name );

