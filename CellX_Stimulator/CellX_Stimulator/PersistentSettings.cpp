#include "PersistentSettings.h"
#include "CRC16.h"
#include <EEPROM.h>

// const int PersistentSettings::CurrentVersion = 2;

bool PersistentSettings::LoadFromEEPROM(){
	Serial.println( "LoadFromEEPROM..." );

	// fetch settings
	EEPROM.get( SettingsAddress, Settings );	// this is some Serious MOJO
	Dump( Settings );

	// verify version, CRC and size

	if( VersionIsInvalid()
	|| SizeIsInvalid()
	|| ChecksumIsInvalid() )
	{
		return false;
	}

	Serial.println( "LoadFromEEPROM success" );
	return true;	// signal success
}

bool PersistentSettings::SaveToEEPROM(){
	// update version, size and Checksum
	Settings.Version = CurrentVersion;
	Settings.Size = sizeof( SettingsStruct );
	ComputeChecksum();

	Serial.println( "SaveToEEPROM..." );
	Dump( Settings );

	// save data to EEPROM
	EEPROM.put( SettingsAddress, Settings );	// this is some Serious MOJO
	return true;	// signal error
}

void PersistentSettings::SetFactoryDefaults(){
	Serial.println( "SetFactoryDefaults" );
	Settings.Version = CurrentVersion;
	Settings.Size = sizeof( SettingsStruct );
	Settings.Checksum = 0xFFFF;
	strncpy( 
		Settings.StartupCommand, 
		DefaultStartupCommand, 
		StartupCommandMaxLen );
}

// validation functions issue messages if there are problems, else they're silent

bool PersistentSettings::VersionIsInvalid(){
	if( Settings.Version < FirstVersion || Settings.Version > CurrentVersion ){
		Serial.print( "LoadFromEEPROM impossible version: " );
		Serial.println( Settings.Version );
		return true;
	}
	
	if( Settings.Version < CurrentVersion ){
		Serial.print( "LoadFromEEPROM upgrading from version " );
		Serial.print( Settings.Version );
		Serial.print( " to " );
		Serial.println( CurrentVersion );

		// fill in missing items and upgrade version
		Settings.SetDefaults();
		Settings.Version = CurrentVersion;
		// TODO: I thought SetDefaults would chain up the inheritance hierarchy
		// but no, you only do this while version > Settings.Version cause
		// that one is already loaded with valid data. Something to worry about
		// if we ever get a 3rd version.
	}

	return false;
}

bool PersistentSettings::SizeIsInvalid(){
	uint expected = 0;

	switch( Settings.Version )
	{
	case 1:
		expected = sizeof( SettingsStructV1 );
	case 2:
		expected = sizeof( SettingsStructV2 );
	}

	if( Settings.Size == expected )
		return false;

	Serial.print( "LoadFromEEPROM size error: expected " );
	Serial.print( expected );
	Serial.print( " but got " );
	Serial.println( Settings.Size );

	return true;
}

bool PersistentSettings::ChecksumIsInvalid(){
	// compare stored Checksum to computed actual
	if( Settings.Checksum == TemporaryChecksum )
		return false;

	Serial.println( "LoadFromEEPROM checksum error" );
	return true;
}

void PersistentSettings::ComputeChecksum(){
	// compute actual Checksum and store it
	Settings.Checksum = TemporaryChecksum;
}

void PersistentSettings::Dump( SettingsStruct& settings ){
	Serial.print( "Version = " );
	Serial.println( settings.Version );
	Serial.print( "Size = " );
	Serial.println( settings.Size );
	Serial.print( "Checksum = " );
	Serial.println( settings.Checksum, HEX );
	Serial.print( "StartupCommand = " );
	Serial.println( settings.StartupCommand );
}

