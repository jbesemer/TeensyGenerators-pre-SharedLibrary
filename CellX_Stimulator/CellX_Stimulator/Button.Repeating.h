#pragma once

#include "Config.h"
#include "Button.h"

// button with Clicks which repeat so long as the button is held down

class RepeatingButton : public Button
{
	elapsedMillis MillisecSinceClick;	// time since last click event

	uint InitialDelay;		// button hold time before first Click event (inclusive of debounce time)
	uint RepeatInterval;	// interval between successive Click events

	bool IsRepeating;		// main operational state
	bool IsWaiting;			// waiting for InitialDelay after first Click

public:
	RepeatingButton(
		int pin,
		uint repeatDelay = 100,
		uint initialDelay = 500,
		uint settlingTime = 50,
		int activeState = LOW )
		: Button( pin, settlingTime, activeState )
		, InitialDelay( initialDelay )
		, RepeatInterval( repeatDelay )
	{
		IsWaiting = IsRepeating = false;
	}

	bool IsStarting(){
		return IsPressed() && NoChangesSince( InitialDelay );
	}

	bool WasClicked(){
		if( IsReleasedState() )
			IsWaiting = IsRepeating = false;

		else {
			if( IsRepeating ){
				if( MillisecSinceClick > RepeatInterval ){
					MillisecSinceClick = 0;
					return true;	// 3rd and subsequent clicks
				}
			}
			else if( IsWaiting ){
				if( IsStarting() ){
					IsRepeating = true;
					MillisecSinceClick = 0;
					return true;	// 2nd Click event
				}
			}
			else if( IsStable() ){		// waiting normal debounce delay for first click
				IsWaiting = true;
				return true;	// first Click event
			}
		}

		return false;			// no Click
	}
};

