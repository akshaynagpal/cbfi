/**
 *
 * malloc() wrapper
 *
 **/

#include "wrapper.h"

typedef void* (*orig_malloc_type)(size_t size);

void *malloc(size_t size){
printf("Malloc");
	char* fail_num = getenv("MALLOC_FAIL");

    if (fail_num != NULL){
    	++global_counts.malloc;

	    // Note: strtok requires the a char* or char[] 
	    // that it can modify and const char* won't work
    	char *num;
    	// Should we use strtok_r which is thread safe?: 
		num = strtok(fail_num,",");
		while(num != NULL){
			if (atol(num) == global_counts.malloc)
            	return NULL;
			num = strtok(NULL,",");
		}
    }
    
    // normal malloc
	orig_malloc_type orig_malloc;
	orig_malloc = (orig_malloc_type)dlsym(RTLD_NEXT,"malloc");
	return orig_malloc(size);
}
