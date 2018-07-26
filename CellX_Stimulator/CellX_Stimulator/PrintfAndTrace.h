#pragma once

#include "Config.h"

// Trace, Printf //////////////////////////////////////////////////////
#define PRINTF_ENABLED 0
#define TRACE_ENABLED 0

#if true

extern bool TraceEnabled;
extern void Trace(const char*fmt, ...);	// don't forget "\n"
extern void Printf(const char*fmt, ...);
#endif
