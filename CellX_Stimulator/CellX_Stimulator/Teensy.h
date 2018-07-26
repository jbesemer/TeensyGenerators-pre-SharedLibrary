// #pragma once

// low-level hardware definitions & functions for Rick's custom gizmo (plus other generic utilities)

// ADC channel assignments to Pots (not all of which may exist):

#if TEENSY_LI
#define P1 A8
#define P2 A7
#define P3 A6

#endif

#if TEENSY_OBIS
// ADC channel assignments to SDR:

#define BPTEMP 	A0		//baseplate temperature
#define PWRMON 	A1		//photodiode output
#define DIOPWR	A2		//diode current


// IO pin assignments to SDR:

#define INUSE 	9		//in, "SDR in use" pin. High if OBIS connected, pull low to enable RS-485 link
#define INHIBIT 10		//out, low to allow OBIS to receive RS-485
#define LSR_RDY	12		//in, high when ready
#define LSR_FLT	22		//in, high when faulted
#define DMOD	23		//out, high to turn laser on. Pin is hardware PWM.
#define nRX_EN	25		//out, low to receive RS-485
#define TX_EN	32		//out, high to transmit RS-485
#endif

#if TEENSY_CELLEX
#endif


// LED ports //////////////////////////////////////////////////////////////////

#if TEENSY_LI
#define LED 13	// Arduino standard on-board LED

#define LED1 3	// Green
#define LED2 4	// Yellow
#define LED3 5	// Orange
#define LED4 6	// Red

#define LED_GREEN 3		// Green	aligned with BUTTON1
#define LED_YELLOW 4	// Yellow	aligned with BUTTON2
#define LED_ORANGE 5	// Orange	aligned with BUTTON3
#define LED_RED 6		// Red		aligned with BUTTON4

#endif

#if TEENSY_OBIS
#define LED 13	// Blue, Arduino standard on-board LED

#define LED1 5	// Green
#define LED2 21	// Yellow
#define LED3 20	// Orange
#define LED4 6	// Red

#define LED_GREEN 5		// Green	aligned with BUTTON1
#define LED_YELLOW 21	// Yellow	aligned with BUTTON2
#define LED_ORANGE 20	// Orange	aligned with BUTTON3
#define LED_RED 6		// Red		aligned with BUTTON4
#endif

extern void LedSet( int ledPin, int isOn );
extern void LedOn( int ledPin );
extern void LedOff( int ledPin );

// button port assignments ////////////////////////////////////////////////////

#if TEENSY_LI
#define BUTTON1 19	// A5	aligned with LED3 / GREEN
#define BUTTON2 18	// A4	aligned with LED4 / YELLOW
#define BUTTON3 17	// A3	aligned with LED5 / ORANGE
#define BUTTON4 16	// A2	aligned with LED6 / RED

#define BUTTON_GREEN 19		// A5	aligned with LED3 / GREEN
#define BUTTON_YELLOW 18	// A4	aligned with LED4 / YELLOW
#define BUTTON_ORANGE 17	// A3	aligned with LED5 / ORANGE
#define BUTTON_RED 16		// A2	aligned with LED6 / RED

#define ONESHOT_BUTTON BUTTON_ORANGE
#define ONESHOT_LED LED_ORANGE

#define VARGAIN_LED LED_GREEN
#define VARGAIN_POT P1

#endif

#if TEENSY_OBIS
#define BUTTON1 33	// A5	aligned with LED3 / GREEN
//#define BUTTON2 18	// A4	aligned with LED4 / YELLOW
//#define BUTTON3 17	// A3	aligned with LED5 / ORANGE
//#define BUTTON4 16	// A2	aligned with LED6 / RED

#define BUTTON_GREEN 33		// A5	aligned with LED3 / GREEN
//#define BUTTON_YELLOW 18	// A4	aligned with LED4 / YELLOW
//#define BUTTON_ORANGE 17	// A3	aligned with LED5 / ORANGE
//#define BUTTON_RED 16		// A2	aligned with LED6 / RED

#endif

#define BUTTON_NONE	0	// returned by AnyButtonPressed if no button is pressed

// map button num (1,2,3,4) to above port nums
#define BUTTON_TO_PORT( BUTTON ) 	\
	((BUTTON)										\
		? ( BUTTON1 + 1 - (BUTTON))		\
		: 0 )

// map above port nums to button num (1,2,3,4)
#define PORT_TO_BUTTON( BUTTON )  	\
	((BUTTON)										\
		? ( BUTTON1 - (BUTTON) + 1 )		\
		: 0 )

// return the other state
extern int OppositeState( int state );

// return 1 iff button is ...
extern int ButtonPressed( int button );		// ...pressed (input is LOW)
extern int ButtonReleased( int button );	// ...released (input is HIGH)

// return 1 if any of the 4 buttons are pressed
extern int AnyButtonPressed();

// Global Firmware assignments of LEDs and Buttons ////////////////////////////

#define ZERO_LED LED_RED
#define ZERO_BUTTON BUTTON1

// #define UNASSIGNED P2
// #define UNASSIGNED P3
// #define UNASSIGNED LED_YELLOW
// #define UNASSIGNED BUTTON_GREEN
// #define UNASSIGNED BUTTON_YELLOW


// Misc. //////////////////////////////////////////////////////////////////////

extern void Teensy_Setup();
extern void show( int pinOff, int pinOn );
extern int FreeRam();
extern void PrintFreeRam();


// Trace, Printf //////////////////////////////////////////////////////

extern bool TraceEnabled;

extern void Trace( const char*fmt, ... );	// don't forget "\n"
extern void Printf( const char*fmt, ... );
