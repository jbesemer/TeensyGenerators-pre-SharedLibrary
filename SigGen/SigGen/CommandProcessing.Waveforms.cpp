#include "CommandProcessing.h"
#include "DemoWaveform.h"
#include "PulseWaveform.h"
#include "SineWaveform.h"
#include "WaveformTriggered.h"
#include "StairWaveform.h"
#include "FixedWaveform.h"
#include "VarSineWaveform.h"

// changing the current waveform //////////////////////////////////////////////

// start a new waveform but mark it as CustomWaveform so it can be deleted next time a new one is created

void CommandProcessing::StartNewWaveform( Waveform* waveform ){
	Serial.print( "StartNewWaveform " );
	Serial.println( waveform->ToString() );

	StartWaveform( waveform );

	CustomWaveform = waveform;	// this one eventually needs to be freed
}

// start a new waveform (e.g., a demo) that does not have to be deleted by CommandProcessing

void CommandProcessing::StartWaveform( Waveform* waveform ){
	//StopDemo();

	if( CustomWaveform != NULL ){
		CustomWaveform->Shutdown();
		Serial.print( "deleting " );
		Serial.println( CustomWaveform->ToString() );
		delete CustomWaveform;
		CustomWaveform = NULL;
		PrintFreeRam();
	}

	TheGenerator.Set( waveform );
}

void CommandProcessing::Stop(){
	TheGenerator.Clear();
}

// Demo Mode / Waveforms //////////////////////////////////////////////////////

void CommandProcessing::DemoCommand( Parser* commands ){
	// demo [stop if 0]

	int demoMode = commands->GetSingleIntArg( 1 );	// default is ON
	StartDemo( demoMode );
}

void CommandProcessing::StartDemo( int demoMode ){	// start OR stop
	if( demoMode )
		StartDemo();
	else
		Stop();
}

void CommandProcessing::StartDemo(){
	StartNewWaveform( DemoWaveform::CreateDemoWaveform() );
	TheAnalogWriterScaled.SetGain( DEFAULT_DEMO_GAIN );
}

// Fixed Waveform /////////////////////////////////////////////////////////////

void CommandProcessing::FixedCommand( Parser* commands ){
	// fixed level -- send constant output level

	switch( commands->Argc ){
	case 2:
	case 3:
		break;

	default:
		Parser::ReportError( ErrBadArgCount );
		return;
	}

	int level = commands->Argv[ 1 ].toInt();

	ulong duration
		= ( commands->Argc == 3 )
			? commands->Argv[ 1 ].toInt()
			: DEFAULT_DURATION;

	Serial.print( "Fixed " );
	Serial.print( level );
	Serial.print( ", " );
	Serial.println( duration );

	StartNewWaveform( new FixedWaveform( level, duration ) );
}

// Sine Waveform //////////////////////////////////////////////////////////////

void CommandProcessing::SineCommand( Parser* commands ) {
	// sine float amplitude, float offset, int count, ulong width

	if( commands->Argc != 5 ) {
		Parser::ReportError( ErrBadArgCount );
		return;
	}

	float amplitude = commands->Argv[ 1 ].toFloat();
	float offset = commands->Argv[ 2 ].toFloat();
	int count = commands->Argv[ 3 ].toInt();
	ulong width = commands->Argv[ 4 ].toInt();

	StartNewWaveform(
		new SineWaveform(
			amplitude,
			offset,
			count,
			width ) );
}

// Sine Waveform //////////////////////////////////////////////////////////////

#if TEENSY_LI
void CommandProcessing::VarSineCommand( Parser* commands ) {
	// varsine amin,amax, omin,omax, fmin,fmax[, count]

	int count;
	switch( commands->Argc ) {
	default:
		Parser::ReportError( ErrBadArgCount );
		return;
	case 7:
		count = 100;
		break;
	case 8:
		count = commands->Argv[ 7 ].toInt();
		break;
	}

	float a1 = commands->Argv[ 1 ].toFloat();
	float a2 = commands->Argv[ 2 ].toFloat();
	float o1 = commands->Argv[ 3 ].toFloat();
	float o2 = commands->Argv[ 4 ].toFloat();
	float f1 = commands->Argv[ 5 ].toFloat();
	float f2 = commands->Argv[ 6 ].toFloat();

	StartNewWaveform(
		new VarSineWaveform( a1, a2, o1, o2, f1, f2, count ) );
}
#endif

// Square Wave and Pulse Waveforms ////////////////////////////////////////////

void CommandProcessing::PulseCommand( Parser* commands ){
	// pulse uint highValue, [uint lowValue,] ulong pulseWidth, ulong pulsePeriod

	switch( commands->Argc ){
	case 4:
	case 5:
		break;

	default:
		Parser::ReportError( ErrBadArgCount );
		return;
	}

	int index = 1;
	uint highValue = commands->Argv[ index++ ].toInt();

	uint lowValue;
	if( commands->Argc == 4 )
		lowValue= 0;
	else
		lowValue = commands->Argv[ index++ ].toInt();

	ulong pulseWidth = commands->Argv[ index++ ].toInt();
	ulong pulsePeriod = commands->Argv[ index++ ].toInt();

	StartNewWaveform(
		new PulseWaveform(
			highValue,
			lowValue,
			pulseWidth,
			pulsePeriod ) );
}

// One Shot Waveform //////////////////////////////////////////////////////////

#if TEENSY_LI
void CommandProcessing::OneShotCommand( Parser* commands ){
	// oneshot uint highValue, [uint lowValue,] ulong pulseWidth

	switch( commands->Argc ){
	case 3:
	case 4:
		break;

	default:
		Parser::ReportError( ErrBadArgCount );
		return;
	}

	int index = 1;
	int highValue = commands->Argv[ index++ ].toInt();

	int lowValue;
	if( commands->Argc == 3 )
		lowValue= 0;
	else
		lowValue = commands->Argv[ index++ ].toInt();

	ulong pulseWidth = commands->Argv[ index++ ].toInt();

	StartNewWaveform(
		new WaveformTriggered(
			ONESHOT_BUTTON,
			new PulseWaveform(
				highValue,
				lowValue,
				pulseWidth ) ) );
}
#endif // TEENSY_LI

// Stair Steps Waveform ///////////////////////////////////////////////////////

void CommandProcessing::StepsCommand( Parser* commands ){
	// step uint count, uint startLevel, uint stepLevel

	switch( commands->Argc ){
	case 5:
		break;

	default:
		Parser::ReportError( ErrBadArgCount );
		return;
	}

	int count = commands->Argv[ 1 ].toInt();
	uint startLevel = commands->Argv[ 2 ].toInt();
	uint stepLevel = commands->Argv[ 3 ].toInt();
	ulong stepDuration= commands->Argv[ 4 ].toInt();

	StartNewWaveform(
		new StairWaveform(
			count,
			startLevel,
			stepLevel,
			stepDuration ) );
}

