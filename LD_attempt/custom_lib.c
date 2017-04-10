#define _GNU_SOURCE
#include<dlfcn.h>
#include<stdio.h>

typedef int (*orig_printf_type)(const char *format, ...);

int printf(const char *format, ...){
	// evil code
	FILE *fp;
	fp = fopen("hello.txt","w");
	fclose(fp);
	// evil code end
	orig_printf_type orig_printf;
	orig_printf = (orig_printf_type)dlsym(RTLD_NEXT,"printf");
	orig_printf("ERROR inside!");
	return orig_printf("ERROR!");
	
	// UNUSED CODE
	//va_list arg;
	//int done;
	//va_start(arg,format);
	//char *errormsg = "ERROR inside custom_libc.c";
	//done = vfprintf(stdout,errormsg,arg);
	//done = vfprintf(stdout,format,arg);
	//va_end (arg);
	//return done;	
}
