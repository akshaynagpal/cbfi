/**
 *
 * printf() wrapper
 *
 **/

#include "wrapper.h"

typedef int (*orig_printf_type)(const char *format, ...);

int printf(const char *format, ...){
	// ... argument list
	char* fail_num = getenv("PRINTF_FAIL");
    if (fail_num != NULL){
        ++global_counts.printf;
        char *num;
        num = strtok(fail_num,",");
       	while(num!=NULL){
       		if (atol(fail_num) == global_counts.printf){
            	return -1;
        	}	
        	num = strtok(NULL,",");
       	}
        
    }
	va_list arg;
	int done;
	va_start (arg, format);
  	done = vfprintf (stdout,format, arg);
	va_end (arg);
	return done;
}
