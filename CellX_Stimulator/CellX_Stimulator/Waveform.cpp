#include "Waveform.h"

Waveform::Waveform()
{
	Allocated = NULL;
	Count = 0; // subclass initializes Count
}

void* Waveform::Allocate( int bytes )
{
	Allocated = malloc( bytes );	// only call to malloc in app
	return Allocated;
}

Waveform::~Waveform()
{
	if( Allocated != NULL )
		free( Allocated );			// only call to free in app
}
