#pragma once

#include "Config.h"

#define MAX_ARGS 8

struct NameIdPair {
	const char* Name;
	int Id;

	NameIdPair( int id, const char* name ){
		Id = id;
		Name = name;
	}
};

class Parser
{
	static const NameIdPair NameIds[];
	static int Count;

	static const char* ErrorMessages[];
	static int ErrorMessageCount;

public:
	String Original;
	String* Argv;
	int Argc;
	bool IsQuery;

	Parser();

	int Parse( String command );
	int ParseCSV( String command );

	int GetSingleIntArg( int Default );

	String ToString();
	String ToString( int start );

	static int Lookup( String name );
	static void ReportError( int errNum, String extra = "" );
};

enum {
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
	CmdShowWaveform,

	CmdSineWave,
	CmdVarSineWave,
	CmdPulse,
	CmdHiLow,
	CmdOneShot,
	CmdSteps,
	CmdFixed,

	CmdGetGain,
	CmdSetGain,
	CmdGetVariableGain,
	CmdSetVariableGain,

	// reserved for DOWNLOAD
	CmdUndefine,
	CmdDefine,
	CmdShowDef,
	CmdLoad,
	CmdStats,
	CmdPlay,
};

enum {
	ErrBadCommand = 101,
	ErrBadArgCount,
	ErrBadArgument,
	ErrBadTestId,
	ErrUnimplemented,
	ErrIllegal,
};

