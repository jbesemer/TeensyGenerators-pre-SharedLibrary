#pragma once

#include "Config.h"
#include "Button.h"
#define TRACE(X) // Trace( X )

// button with a state that toggles each time there is a click

class ToggleButton : public Button
{
public:
	ToggleButton( int pin, uint settlingTime = 50, int activeState = LOW )
		: Button( pin, settlingTime, activeState )
	{
		ToggleState= false;
	}

	int ToggleState;					// state of the toggle

	// toggle ToggleState it each time there is a Click event.
	// return true iff it changed this time 

	bool WasToggled(){
		if( WasClicked() ){
			ToggleState = !ToggleState;
			TRACE( ToggleState
					? "ToggledOn"
					: "ToggledOff" );
			return true;
		}

		// Serial.println( "not Toggled" );
		return false;
	}

	// rising edge of IsToggledOn

	bool WasToggledOn(){
		return !ToggleState && WasToggled();
	}

	// falling edge of IsToggledOn

	bool WasToggledOff(){
		return ToggleState && WasToggled();
	}
};


