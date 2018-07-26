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
#define ZERO_BUTTON BUTTON1

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

#define LED_GREEN 5		// Green
#define LED_YELLOW 21	// Yellow
#define LED_ORANGE 20	// Orange
#define LED_RED 6		// Red

// button port assignments ////////////////////////////////////////////////////

#define BUTTON1 33
//#define BUTTON2 18
//#define BUTTON3 17
//#define BUTTON4 16

#define BUTTON_GREEN 33
//#define BUTTON_YELLOW 18
//#define BUTTON_ORANGE 17
//#define BUTTON_RED 16

#define BUTTON_NONE	0	// returned by AnyButtonPressed if no button is pressed

