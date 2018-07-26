#pragma once

#include "Config.h"
#include "SettingsStruct.h"

#define TemporaryChecksum ((uint)0xF00F)

class PersistentSettings {
public:
	//const int StartupCommandMaxLen = 255;
	const int CurrentVersion = 2;
	const int FirstVersion = 1;
	const int MaxSizeEEPROM = 2048;	// we're using a tiny fraction of this
	const int SettingsAddress = 0;

	const char* DefaultStartupCommand = "demo";

	SettingsStruct Settings;

	PersistentSettings(){
	}

	bool LoadFromEEPROM();
	bool SaveToEEPROM();
	void SetFactoryDefaults();

	bool VersionIsInvalid();
	bool SizeIsInvalid();
	bool ChecksumIsInvalid();
	void ComputeChecksum();
	void Dump( SettingsStruct& settings );
};