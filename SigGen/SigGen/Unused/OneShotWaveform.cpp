#include "OneShotWaveform.h"

// The waveform generator calls this entrypoint once every generation cycle.
// We wait for a button to be pressed and released, then output the waveform once.

void OneShotWaveform::Play( Generator* generator )
{
	if( Button == BUTTON_NONE ){
		LedOn( LED_GREEN );

		// if no button has been pressed, wait for one to be pressed
		LedOn( LED_YELLOW );
		int pressed = AnyButtonPressed();
		LedOff( LED_YELLOW );

		if( pressed != BUTTON_NONE ){
			Button = pressed;
			Serial.print( "Button " );
			Serial.print( PORT_TO_BUTTON( Button ));
			Serial.println( " Pressed" );
		} else {

			if( !MessageSent ){
				Serial.println( "Press any button to send pulse" );
				MessageSent = 1;
			}
		}
	} else {
		// button has been pressed, wait for it to be released
		if( !ButtonPressed( Button )){
			Serial.println( "Sending pulse" );

			LedOff( LED_GREEN );
			LedOn( LED_RED );

			// clear waiting for button to be released state
			Button = BUTTON_NONE;
			MessageSent = 0;

			// run the waveform
			TheWaveform->Play( generator );

			LedOff( LED_RED );
		}
	}
}
