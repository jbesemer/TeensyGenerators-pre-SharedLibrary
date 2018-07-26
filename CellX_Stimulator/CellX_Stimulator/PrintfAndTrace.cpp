#include "PrintfAndTrace.h"

// Trace, Printf //////////////////////////////////////////////////////

#if PRINTF_ENABLED||TRACE_ENABLED
// undef messages here evidently are bugs in VS highlighting, not the code itself
#include <stdarg.h> 
#endif

bool TraceEnabled = false;

#if TRACE_ENABLED
void Trace(const char* fmt, ...) {
	if (!TraceEnabled)
		return;

	char buf[128]; // resulting string limited to 128 chars
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, 128, fmt, args);
	va_end(args);
	Serial.print(buf);
}
#endif

#if PRINTF_ENABLED
void Printf(const char* fmt, ...) {
	char buf[128]; // resulting string limited to 128 chars
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, 128, fmt, args);
	va_end(args);
	Serial.print(buf);
}
#endif
