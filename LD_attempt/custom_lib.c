#define _GNU_SOURCE
#include<dlfcn.h>
#include<stdio.h>

typedef int (*orig_printf_type)(const char *format, ...);

int printf(const char *format, ...){
	// evil code - a file is created on every printf
	FILE *fp;
	fp = fopen("hello.txt","w");
	fclose(fp);
	// evil code end
	orig_printf_type orig_printf;
	orig_printf = (orig_printf_type)dlsym(RTLD_NEXT,"printf");
	return orig_printf("ERROR!");	// whatever the user gives, it prints error only
}
