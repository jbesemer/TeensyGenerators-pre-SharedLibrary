// Config.h -- global configuration switch and options

#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

// board specifics

// only define one of these

#define TEENSY_LI			0	// original "Li" board
#define TEENSY_OBIS		1	// revisions for modulating obis lasers
#define TEENSY_CELLEX	0	// revisions for cellex version

#include "Teensy.h"

// app configuration

#define DATE "2-Jun-2017 14:00"
#define VERSION "0.0.1"
#define MODEL = "Teensy 3.1"

#define ENABLE_DOWNLOAD_COMMANDS	0	// downloading is work in progress

// preferred abbreviations

typedef unsigned int uint;		// 16 bits
typedef unsigned long ulong;	// 32 bits

