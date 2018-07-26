#pragma once

#include "Config.h"
#include "AnalogWriter.h"
#include "QuadMux.h"

class AnalogWriterMux : public AnalogWriter
{
protected:
	QuadMux* TheMux;
	int Addr;

public:
	AnalogWriterMux(QuadMux* mux, int addr = LTC2636_DAC_A) {
		TheMux = mux;
		Addr = addr;
	}

	void Reset() { TheMux->Reset(); }

	void SetAddr(int addr) { Addr = addr; }

	// override WriteRaw
	void WriteRaw(uint value) { TheMux->Write(Addr, value); }

};

