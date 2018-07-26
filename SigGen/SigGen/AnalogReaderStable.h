#pragma once
#pragma once

#include "AnalogReader.h"
#include "Stabalizer.h"

// modify Changed() predicate so that it only returns true if the condition
// has remained stable for specified interval.


class AnalogReaderStable: public AnalogReader
{
protected:
	Stabalizer Stable;

public:

	AnalogReaderStable( int pin, uint milliseconds )
		: AnalogReader( pin )
		, Stable( milliseconds )
	{
		InitFilter();
	}

	bool Changed() { return Stable.HasSettled( AnalogReader::Changed() ); }
	bool Changed( uint threshold ) { return Stable.HasSettled( AnalogReader::Changed( threshold ) ); }
};
