#pragma once
#include "Config.h"
#include "ToggleMode.h"
#include "QuadMux.h"
#include "AnalogWriterMux.h"

class CellX_Demo : public ToggleMode
{
protected:
	int Index;
	AnalogWriterMux* MuxWriter;

	void PlayWaveform( int index );
public:
	CellX_Demo(AnalogWriterMux* aMux, int buttonPin )
		: ToggleMode(buttonPin)
	{
		MuxWriter = aMux;
	}

	virtual void Loop();		// called from main loop; override implements mode when Active
	virtual void Startup();		// override implements when mode toggles on
	virtual void Shutdown();	// override implements when mode toggles off
};

extern int CellX_Demo_Dacs[];
extern int CellX_Demo_Leds[];
extern int CellX_DMOD[];
extern int CellX_Demo_DacCount;
extern int CellX_Demo_LedCount;
extern void ClearAllLEDs();
extern void SetAllDmod(int value);
extern void SetDmod(int dmod, int value);
extern void ToggleKeyswitch();
