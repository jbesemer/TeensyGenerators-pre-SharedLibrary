#pragma once

#include "AnalogReader.h"

#define DefaultSettleTime 100

class AnalogReaderFiltered : public AnalogReader
{
protected:

public:
	uint Current;	// weighted history including most recent sample
	uint History;	// weighted history excluding most recent sample

	elapsedMillis MillisecSinceChange;	// time since last state change 
	uint SettleTime;	// interval defining IsStable

	bool WaitStable;	// flag waiting for value to stabalize after a change

	void Clear() {
		Current = History = AnalogReader::Current;
		WaitStable = false;
	}

	bool IsStable( uint ms ) { return MillisecSinceChange > ms; }
	bool IsStable() { return IsStable( SettleTime ); }

	AnalogReaderFiltered( int pin, uint settleTime = DefaultSettleTime )
		: AnalogReader( pin )
	{
		SettleTime = settleTime;
		Clear();
	}

	// a simple, clumsy but effective filter: 
	// a weighted average of the ADC_BITS most recent samples

	uint ReadFiltered() {
		History = Current;
		Current = ( Current + Read() ) >> 1;

		// a change is any time current no longer matches history
		if( History != Current ) {
			MillisecSinceChange = 0;	// reset timer
			WaitStable = true;			// we have a change but not yet stable
		}

		return Current;
	}

	// see if there have been changes but they have settled

	bool Changed() {
		ReadFiltered();

		if( WaitStable && IsStable() ) {
			// signal change just this one time and reset mech
			WaitStable = false;
			return true;
		}

		// else still waiting
		return false;
	}

	// fetch current value and reset change detection mechanism

	float GetValue() {
		WaitStable = false;
		return Current;
	}

	virtual String ToString() {
		String r = "AnalogReaderFiltered( ";
		r.append( Pin );
		r.append( ", " );
		r.append( SettleTime );
		r.append( " )" );

		return r;
	}

	virtual String ToStringEx() {
		String r = ToString() + ": ";
		r.append( Current );
		r.append( ", " );
		r.append( Current );
		r.append( ", " );
		r.append( History );
		r.append( ", " );
		ulong ms = MillisecSinceChange;
		r.append( ms );
		r.append( ", " );
		r.append( IsStable() ? "STABLE" : "Not Stable" );

		return r;
	}
};

