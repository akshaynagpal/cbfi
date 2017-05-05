/**
 *
 * malloc() wrapper
 *
 **/

#include "wrapper.h"

typedef void* (*orig_malloc_type)(size_t size);

void *malloc(size_t size){
	printf("Malloc");
	fflush(NULL);
	/*void *array[10];
	size_t size_call;
	printf("Stack Trace Start for\n");
	size_call = backtrace(array, 10);
	backtrace_symbols_fd(array, size_call, 2);
	printf("Stack Trace End\n");
	char* fail_nums = getenv("MALLOC_FAIL");

    if (fail_nums != NULL){
    	++global_counts.malloc;

	    // Note: strtok requires the a char* or char[] 
	    // that it can modify and const char* won't work
    	char *num;
    	// Should we use strtok_r which is thread safe?: 
		num = strtok(fail_nums,",");
		while(num != NULL){
			if (atol(num) == global_counts.malloc)
            	return NULL;
			num = strtok(NULL,",");
		}
    }*/
    
    // normal malloc
	orig_malloc_type orig_malloc;
	orig_malloc = (orig_malloc_type)dlsym(RTLD_NEXT,"malloc");
	return orig_malloc(size);
}
