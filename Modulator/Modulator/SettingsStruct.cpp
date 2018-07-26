#include "SettingsStruct.h"
#include "PersistentSettings.h"
#include "CommandProcessing.h"
#include "AnalogWriter.h"

void SettingsStructV2::SetDefaults(){
	VariableGainEnabled = CommandProcessing::VariableGainEnabledDefault;
	Gain = UNITY_GAIN;
}
