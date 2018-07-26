#pragma once

#include "Config.h"

#define StartupCommandMaxLen  128

struct SettingsStructV1 {
	int Version;
	uint Size;
	uint Checksum;
	char StartupCommand[ StartupCommandMaxLen ];

	void SetStartupCommand( String s ){
		s.toCharArray(
			StartupCommand,
			StartupCommandMaxLen );
	}

	virtual void SetDefaults(){
	}
};

struct SettingsStructV2 : public SettingsStructV1 {
	bool VariableGainEnabled;
	float Gain;

	virtual void SetDefaults();
};

struct SettingsStruct : public SettingsStructV2 {
};

