#include "Config.h"
// #include "TeensyOBIS.h" // included by Config.h

void TeensyOBIS_Setup(){
	Serial1.begin( 921600 ); 		//see: https://www.pjrc.com/teensy/td_uart.html

	pinMode( LED, OUTPUT );
	pinMode( LED1, OUTPUT );
	pinMode( LED2, OUTPUT );
	pinMode( LED3, OUTPUT );
	pinMode( LED4, OUTPUT );

	pinMode( BUTTON1, INPUT_PULLUP );

	pinMode( INHIBIT, OUTPUT );
	digitalWrite( INHIBIT, HIGH );	//disable RS-485 deception by OBIS for now
	
	pinMode( DMOD, OUTPUT );
	digitalWrite( DMOD, LOW );		//turn laser off to start
	
	pinMode( nRX_EN, OUTPUT );		//enable TX & RX for loop back testing
	digitalWrite( DMOD, LOW );
	pinMode( TX_EN, OUTPUT );
	digitalWrite( DMOD, HIGH );	

	pinMode( INUSE, INPUT_PULLDOWN ); //OBIS will pull high if connected, force low to talk RS-485
		
	show( LED, LED1 );
	show( LED1, LED2 );
	show( LED2, LED3 );
	show( LED3, LED4 );
	show( LED4, LED );
	
	// if this function is undefined, you probably have the wrong device selected in your tool chain
	analogWriteResolution( DAC_BITS);
	analogReadResolution( ADC_BITS );
}
