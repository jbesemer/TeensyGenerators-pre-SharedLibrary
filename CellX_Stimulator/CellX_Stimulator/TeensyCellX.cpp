#include "Config.h"
#include "AnalogReader.h"
#include "AnalogWriter.h"
#include <SPI.h>
#include "QuadMux.h"

// #include "TeensyCellX.h" // included by Config.h

void TeensyCellX_Setup(){
	Serial1.begin(115200); 		//see: https://www.pjrc.com/teensy/td_uart.html
	Serial.begin(115200);

	pinMode( LED, OUTPUT );
	pinMode( LED1, OUTPUT );
	pinMode( LED2, OUTPUT );
	pinMode( LED3, OUTPUT );
	pinMode( LED4, OUTPUT );

	pinMode( BUTTON1, INPUT_PULLUP );
	
	pinMode( PRES232, INPUT_PULLDOWN );	

	pinMode( REDYOUT, INPUT_PULLDOWN );
	pinMode( STBYOUT, INPUT_PULLDOWN );
	pinMode( FALTOUT, INPUT_PULLDOWN );
	pinMode( REDOUT, INPUT_PULLDOWN );
	pinMode( GRNOUT, INPUT_PULLDOWN );
	pinMode( BLUOUT, INPUT_PULLDOWN );	
	
	pinMode( DMOD1, OUTPUT );
	digitalWrite( DMOD1, LOW );		//turn laser off to start
	pinMode( DMOD2, OUTPUT );
	digitalWrite( DMOD1, LOW );		//turn laser off to start
	pinMode( DMOD3, OUTPUT );
	digitalWrite( DMOD1, LOW );		//turn laser off to start
	pinMode( DMOD4, OUTPUT );
	digitalWrite( DMOD1, LOW );		//turn laser off to start	
	pinMode( ExtDmod, OUTPUT );
	digitalWrite( ExtDmod, HIGH );	//get control
	
	pinMode( ExtAmod, OUTPUT );
	digitalWrite( ExtAmod, HIGH );	//get control	
	
	pinMode( SHDN, OUTPUT );
	digitalWrite( SHDN, LOW );		//enable unit		
	pinMode( KeyOn, OUTPUT );
	digitalWrite( KeyOn, HIGH );	//enable unit	
	pinMode( IntlkOn, OUTPUT );
	digitalWrite( IntlkOn, HIGH );	//enable unit		
	
	pinMode( nLDAC, OUTPUT );		//SPI init
	digitalWrite( nLDAC, HIGH );	
	pinMode( nSPICS, OUTPUT );	
	digitalWrite( nSPICS, HIGH );	
	pinMode( nCLR, OUTPUT );
	digitalWrite( nCLR, HIGH );

	QuadMux TheMux(SCK, nSPICS);	// temporary instance for Reset
	TheMux.Reset();

	show( LED, LED1 );
	LedOn( LED );
	show( LED1, LED2 );
	show( LED2, LED3 );
	show( LED3, LED4 );
	show( LED4, LED );
	
	// if this function is undefined, you probably have the wrong device selected in your tool chain
	analogWriteResolution( DAC_BITS);
	analogReadResolution( ADC_BITS );
}

