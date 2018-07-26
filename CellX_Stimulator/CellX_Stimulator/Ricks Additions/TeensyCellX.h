// #pragma once

// low-level hardware definitions & functions for Rick's custom gizmo (plus other generic utilities)

// ADC channel assignments:


// IO pin assignments to DB37:

#define nLDAC 	2		//out, load DAC strobe
#define ExtAmod 3		//out, high to use AMOD pins
#define SHDN	4		//out, high to turn off CellX
#define REDYOUT 8		//in, status LED input
#define DMOD3	9		//out, high to turn CH3 on. Pin is hardware PWM
#define DMOD4	10		//out, high to turn CH4 on. Pin is hardware PWM
#define MOSI	11		//out, SPI out
#define MISO	12		//in, SPI in
#define SCK		14		//out, SPI clk
#define nSPICS	15		//out, SPI chip select
#define GRNOUT  16		//in, status LED input
#define BLUOUT  17		//in, status LED input
#define DMOD2	22		//out, high to turn CH2 on. Pin is hardware PWM
#define DMOD1	23		//out, high to turn CH1 on. Pin is hardware PWM
#define ExtDmod 24		//out, high to use DMOD pins
#define KeyOn	25		//out, high to turn on keyswitch
#define PRES232 27		//in, RS-232 active
#define nCLR    28		//out, DAC control
#define STBYOUT 32		//in, status LED input
#define FALTOUT 32		//in, status LED input
#define IntlkOn	31		//out, high to turn on interlock
#define REDOUT  32		//in, status LED input


// Global Firmware assignments of LEDs and Buttons ////////////////////////////

#define ZERO_LED LED_RED
#define ZERO_BUTTON BUTTON_RED

#define ONESHOT_BUTTON BUTTON_ORANGE
#define ONESHOT_LED LED_ORANGE

//#define VARGAIN_LED LED_GREEN
//#define VARGAIN_POT P1
// #define UNASSIGNED P2
// #define UNASSIGNED P3
// #define UNASSIGNED LED_YELLOW
// #define UNASSIGNED BUTTON_GREEN
// #define UNASSIGNED BUTTON_YELLOW

// LED ports //////////////////////////////////////////////////////////////////

#define LED 13	// Blue, Arduino standard on-board LED

#define LED1 5	// Green
#define LED2 21	// Yellow
#define LED3 20	// Orange
#define LED4 6	// Red

#define LED_GREEN 5		// Green	aligned with BUTTON1
#define LED_YELLOW 21	// Yellow	aligned with BUTTON2
#define LED_ORANGE 20	// Orange	aligned with BUTTON3
#define LED_RED 6		// Red		aligned with BUTTON4

extern void LedSet( int ledPin, int isOn );
extern void LedOn( int ledPin );
extern void LedOff( int ledPin );

// button port assignments ////////////////////////////////////////////////////

#define BUTTON1 33	// A5	aligned with LED3 / GREEN
//#define BUTTON2 18	// A4	aligned with LED4 / YELLOW
//#define BUTTON3 17	// A3	aligned with LED5 / ORANGE
//#define BUTTON4 16	// A2	aligned with LED6 / RED

#define BUTTON_GREEN 33		// A5	aligned with LED3 / GREEN
//#define BUTTON_YELLOW 18	// A4	aligned with LED4 / YELLOW
//#define BUTTON_ORANGE 17	// A3	aligned with LED5 / ORANGE
//#define BUTTON_RED 16		// A2	aligned with LED6 / RED

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

// Analog I/O /////////////////////////////////////////////////////////////////

// The Teensey ADC has 12 bits, but the circuit is rather noisy.
// Selecting fewer bits throws away the low order ones, which helps discount the noise.

#define ADC_BITS 10
#define ADC_MAX ( 1 << ADC_BITS )

// The Teensey DAC is on A14, has 12 bits, and we want them all

#define DAC_PIN A14		//AMOD to SDR

#define DAC_BITS 12
#define DAC_MAX ( 1 << DAC_BITS )

#define DAC_MAX_VOLTS 3.5 	// supply rail = output for DAC_MAX
#define METER_MAX_VOLTS 2.2	// 200 W on Heisenberg	( there's a different max for Meterless)

#define VOLTS_TO_BITS( VOLTS ) ((uint)( DAC_MAX * VOLTS / DAC_MAX_VOLTS ))
#define METER_MAX VOLTS_TO_BITS( METER_MAX_VOLTS )

extern void WriteDacRaw( int value );
extern void WriteDac( int value );
extern uint ReadAdc( int channel );
extern uint ReadAdcFiltered( int channel );

// Misc. //////////////////////////////////////////////////////////////////////

extern void LiTeensy_Setup();
extern void show( int pinOff, int pinOn );
extern int FreeRam();
extern void PrintFreeRam();


// Trace, Printf //////////////////////////////////////////////////////

extern bool TraceEnabled;

extern void Trace( const char*fmt, ... );	// don't forget "\n"
extern void Printf( const char*fmt, ... );
