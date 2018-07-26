#pragma once

#include "Config.h"
#include "NameIdPair.h"

#define MAX_ARGS 8

class Parser
{
public:
	String Original;
	String* Argv;
	int Argc;
	bool IsQuery;

	Parser();

	int Parse( String command );
	int ParseCSV( String command );

	int GetSingleIntArg(int Default);
	int GetIntArg(int index);

	String ToString();
	String ToString( int start );

	static int Lookup(String name);
	static int Lookup(String name, const NameIdPair* table, const int count );
};

extern const NameIdPair NameIds[];
extern int NameIdsCount;

extern void ReportError(int errNum, String extra = "");
extern const char* ErrorMessages[];
extern int ErrorMessageCount;

enum {
	ErrBadCommand = 101,
	ErrBadArgCount,
	ErrBadArgument,
	ErrBadTestId,
	ErrUnimplemented,
	ErrUnrecognizedName,
	ErrValueRange,
	ErrIllegal,
};

