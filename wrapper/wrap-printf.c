#define _GNU_SOURCE

#include <stdarg.h>
#include<stdio.h>
#include<dlfcn.h>

typedef int (*orig_printf_type)(const char *format, ...);

int printf(const char *format, ...){
	orig_printf_type orig_printf;
	orig_printf = (orig_printf_type)dlsym(RTLD_NEXT,"printf");
	// ... argument list
	va_list arg;
	int done;
	va_start (arg, format);
  	done = vfprintf (stdout,format, arg);
	va_end (arg);
	return done;
	// return orig_printf("ERROR!");	// whatever the user gives, it prints error only
	// return done;
}
