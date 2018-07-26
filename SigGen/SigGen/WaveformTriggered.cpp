#include "WaveformTriggered.h"

// The waveform generator calls this entrypoint once every generation cycle.
// We wait for a button to be pressed and released, then output the waveform once.

#if TEENSY_LI
void WaveformTriggered::Play( AnalogWriter* writer )
{
	if( !Waiting ){
		Waiting = true;
		LedOn( ONESHOT_LED );
		Serial.println( "Press button 3 to send pulse" );
	}

	if( TriggerButton.WasClicked() ){
		Serial.println( "Sending waveform..." );
		TheWaveform->Play( writer );
		LedOff( ONESHOT_LED );
		Waiting = false;
	}
}

void WaveformTriggered::Shutdown()
{
	LedOff( ONESHOT_LED );
}

#endif // TEENSY_LI
