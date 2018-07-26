#include "Generator.h"

Generator::Generator()
{
}

void Generator::Loop()
{
	if( CurrentWaveform != NULL )
		CurrentWaveform->Play( Writer );
}
