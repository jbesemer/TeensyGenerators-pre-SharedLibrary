#include "HiLowWaveform.h"

//	HiLowWaveform -- outputs a high value followed by a low value,
//		each of a specific duration. (Optimized for speed vs. HiLowWaveform.)

void HiLowWaveform::Init(int highValue, int lowValue, ulong highWidth, ulong lowWidth)
{
	//	int count = 2;
	//	Sample* samples = new Sample[ count ];

	HighValue = highValue;
	LowValue = lowValue;
	HighWidth = highWidth;
	LowWidth = lowWidth;
}

String HiLowWaveform::ToString() {
	String r = "HiLow ";
	r.append(HighValue);
	r.append(", ");
	r.append(LowValue);
	r.append(", ");
	r.append(HighWidth);
	r.append(", ");
	r.append(LowWidth);
	return r;
}

void HiLowWaveform::Play(AnalogWriter* writer)
{
	elapsedMicros elapsed;
	ulong time = HighWidth;

	writer->WriteRaw(HighValue);
	while (time > elapsed)
		continue;

	time += LowWidth;
	writer->WriteRaw(LowValue);
	while (time > elapsed)
		continue;
}

