#pragma once

#include "Config.h"

// Default constructor assumes button shorts input pin to ground 
// with internal pullup enabled (active low).

// Button with debounced events: IsPressed, IsReleased, WasClicked

class Button
{
protected:

	// constants

	const int InputState = INPUT_PULLUP;// change to INPUT if your circuit requires it
	int PressedState, ReleasedState;	// allows active-high or active-low
	uint SettlingTime;					// settling time for button press or release
	int Pin;							// pin wired to button

	// instance data

	int State;					// most recent observed state of the button
	bool WaitRelease = false;	// intermediate state for WasClicked
	elapsedMillis MillisecSinceChange;	// time since last change 

	// update State and reset timer if any change

	int Read(){
		int state = digitalRead( Pin );
		if( state != State )
			MillisecSinceChange = 0;
		State = state;
		return State;
	}

	bool IsPressedState(){ return Read() == PressedState; }

	bool IsReleasedState(){ return Read() == ReleasedState; }

	bool NoChangesSince( uint settlingTime ){ return MillisecSinceChange > settlingTime; }

	bool IsStable(){ return NoChangesSince( SettlingTime ); }

	int OppositeState( int state ){
		if( state == HIGH )
			return LOW;
		else
			return HIGH;
	}

public:

	Button( int pin, uint settlingTime = 50, int activeState = LOW ){
		// initialize constants
		Pin = pin;
		SettlingTime = settlingTime;
		PressedState = activeState;
		ReleasedState = OppositeState( activeState );;

		pinMode( Pin, InputState );	// makes it unnecessary to setup elsehwere

		// reset state & history

		State = ReleasedState;

		WaitRelease = false;
	}

	// button is Pressed or Released and "Debounced"

	bool IsPressed(){ return IsPressedState() && IsStable(); }

	bool IsReleased(){ return IsReleasedState() && IsStable(); }

	// WasClicked happens when a IsPressed occurs 
	// and cannot re-occur until IsReleased

	virtual bool WasClicked(){
		if( WaitRelease ){
			if( IsReleased() )
				WaitRelease = false;
		}
		else if( IsPressed() ){
			WaitRelease = true;
			return true;		// Click event
		}

		return false;		// no Click event
	}
};


#if false	// sort of worked but imperfect

	// Clicked is a sequence of a Press followed by a Release, 
	// each sufficiently debounced.

	// NO GOOD: wait for button Up is correct for mouse clicks 
	// (because the mouse may move when down); but making the user 
	// wait is clearly wrong for buttons.

	virtual bool WasClickedOriginal(){
		if( IsPressed ){
			if( IsReleased() ){
				// reset history, ready for next click
				IsPressed = IsReleased = false;
				return true;
			}
		}
		else {
			IsPressed();	// poll for pressed event
		}

		return false;
	}
};

#endif
