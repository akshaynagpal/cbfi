/**
 *
 * printf() wrapper
 *
 **/

#include "wrapper.h"

typedef int (*orig_printf_type)(const char *format, ...);

int printf(const char *format, ...){
	// ... argument list
	va_list arg;
	int done;
	va_start (arg, format);
  	done = vfprintf (stdout,format, arg);
	va_end (arg);
	return done;
}
