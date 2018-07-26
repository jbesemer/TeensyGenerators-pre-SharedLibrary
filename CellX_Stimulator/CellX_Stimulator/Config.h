// Config.h -- global configuration switch and options

#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

// board specifics

#include "TeensyCellX.h"
#include "TeensyMisc.h"

// app configuration (mainly for IdentifyCommand)

#define VERSION "1.0.4"
#define DATE "15-mar-2018 12:26"
// #define DATE "14-mar-2018 15:46"	// "Pi" day

#define APPNAME "Jaeger Stimulator"
#define MODEL "Teensy 3.1"
#define AUTHOR "JB, Inc"

#define ENABLE_DOWNLOAD_COMMANDS	0	// downloading is work in progress

// preferred abbreviations

typedef unsigned int uint;		// 16 bits
typedef unsigned long ulong;	// 32 bits

