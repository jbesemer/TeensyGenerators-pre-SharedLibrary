void Generator::SetZeroing( int zeroingMode )
{
	if( zeroingMode ){
		if( !Zeroing ){
			DacWrite( DacZero );
		}
		Serial.println( "Begin Zeroing..." );
	}
	else
	{
		Serial.println( "... Done Zeroing" );
	}

	Zeroing = zeroingMode;
}


uint PrevAdc = 0;
int WasZeroing = 0;
int Toggle = 0;

Waveform* PreZeroWaveform;

