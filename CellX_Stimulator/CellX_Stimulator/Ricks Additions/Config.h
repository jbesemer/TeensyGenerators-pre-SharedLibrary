// Config.h -- global configuration switch and options

#pragma once

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

// board specifics

#include "TeensyOBIS.h"

// app configuration

#define DATE "24-May-2017 17:00"
#define VERSION "0.0.1"
#define MODEL = "Teeny 3.1"

#define ENABLE_DOWNLOAD_COMMANDS	1	// downloading is work in progress

// preferred abbreviations

typedef unsigned int uint;		// 16 bits
typedef unsigned long ulong;	// 32 bits

