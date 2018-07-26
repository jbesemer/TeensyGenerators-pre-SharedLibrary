#include "CommandProcessing.h"
#include "QuadMux.h"
#include "AnalogWriterMux.h"




const NameIdPair ChanNameTable[] = {
	{ LTC2636_DAC_A,	"a" },
	{ LTC2636_DAC_B,	"b" },
	{ LTC2636_DAC_C,	"c" },
	{ LTC2636_DAC_D,	"d" },
	{ LTC2636_DAC_A,	"1" },
	{ LTC2636_DAC_B,	"2" },
	{ LTC2636_DAC_C,	"3" },
	{ LTC2636_DAC_D,	"4" },
};

const int ChanNameCount = sizeof(ChanNameTable) / sizeof(ChanNameTable[0]);

// Syntax: dac chan,value
// chan=A..D --or-- 1..4, value 0..4095

void DacCommand(Parser* parser) {
	if (parser->Argc != 3) {
		ReportError(ErrBadArgCount, "Expecting chan,value");
		return;
	}
	String name = parser->Argv[1];
	int value = parser->GetIntArg(2);

	int addr = TheParser.Lookup(name, ChanNameTable, ChanNameCount);
	if (addr < 0) {
		ReportError(ErrUnrecognizedName, name);
		return;
	}

	if (value < 0 || value > QUADMUX_MAXVALUE) {
		ReportError(ErrValueRange, parser->Argv[2]);
		return;
	}

	TheMux.Write(addr, value);
}

// Set arg names

const NameIdPair SetNameTable[] = {
	{ ExtAmod,	"amod" },
	{ SHDN,		"shdn" },
	{ DMOD4,	"dmod4" },
	{ DMOD3,	"dmod3" },
	{ DMOD2,	"dmod2" },
	{ DMOD1,	"dmod1" },
	{ ExtDmod,	"dmod" },
	{ KeyOn,	"key" },
	{ IntlkOn,	"lock" },
};

int SetNameCount = sizeof(SetNameTable) / sizeof(SetNameTable[0]);

// Syntax: set name,value

void SetCommand(Parser* parser) {
	if (parser->Argc != 3) {
		ReportError(ErrBadArgCount, "Expecting name,value");
		return;
	}
	String name = parser->Argv[1];
	int value = parser->GetIntArg(2);
	int port = TheParser.Lookup(name, SetNameTable, SetNameCount );
	if (port >= 0) {
		digitalWrite(port, value);
	}
	else {
		ReportError(ErrUnrecognizedName, name );
	}
}

const NameIdPair GetNameTable[] = {
	{ REDYOUT,	"RedY" },
	{ GRNOUT,	"Green" },
	{ BLUOUT,	"Blue" },
	{ PRES232,	"Pres232" },
	{ STBYOUT,	"Standby" },
	{ FALTOUT,	"Fault" },
	{ REDOUT,	"Red" },
};

int GetNameCount = sizeof(GetNameTable) / sizeof(GetNameTable[0]);

// Syntax: get [name,...]

void GetCommand(Parser* parser) {
	if (parser->Argc <= 1) {
		// show all
		Serial.println("Inputs:");
		for (int index = 0; index < GetNameCount; index++) {
			const char* name = GetNameTable[index].Name;
			int port = GetNameTable[index].Id;
			ShowPin(name, port);
		}

		Serial.println("Outputs:");
		for (int index = 0; index < SetNameCount; index++) {
			const char* name = SetNameTable[index].Name;
			int port = SetNameTable[index].Id;
			ShowPin(name, port);
		}
	}
	else {
		// show named
		for (int index = 1; index < parser->Argc; index++) {
			String name = parser->Argv[index];
			ShowPin(name);
		}
	}

	Serial.println();
}

void ShowPin(String name, int port) {
	int value = digitalRead(port);
	Serial.print("Get ");
	Serial.print(name);
	Serial.print(" = ");
	Serial.println(value);
}

void ShowPin(String name) {
	int port = TheParser.Lookup(name, GetNameTable, GetNameCount);
	if (port < 0) {
		port = TheParser.Lookup(name, SetNameTable, SetNameCount);
		if (port < 0) {
			ReportError(ErrUnrecognizedName, name);
		}
	}
	ShowPin(name, port);
}

void CellX_Help(){
	Serial.println( "\nCellX Commands:" );
	Serial.println( "dac chan,value	// set dac output level" );
	Serial.print( "    chan: " );
	for( int i = 0; i < ChanNameCount; i++ ){
		if( i > 0 )
			Serial.print( ", " );
		Serial.print( ChanNameTable[ i ].Name );
	}
	Serial.println( "" );
	Serial.println( "    level: 0..4093" );

	Serial.println( "set name,value	// set output port value" );
	Serial.println( "    value: 0, 1 for Low, High" );
	Serial.print( "    names: " );
	for( int i = 0; i < SetNameCount; i++ ){
		if( i > 0 )
			Serial.print( ", " );
		Serial.print( SetNameTable[ i ].Name );
	}
	Serial.println( "" );

	Serial.println( "get [name,...]	// read and show input port values" );
	Serial.print( "    names: " );
	for( int i = 0; i < GetNameCount; i++ ){
		if( i > 0 )
			Serial.print( ", " );
		Serial.print( GetNameTable[ i ].Name );
	}
	Serial.println( "" );
	Serial.println( "           [set names (above) also are valid]" );
}

