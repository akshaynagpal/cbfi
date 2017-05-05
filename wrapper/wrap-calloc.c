/**
 *
 * calloc() wrapper
 *
 **/

#include "wrapper.h"

typedef void* (*orig_calloc_type)(size_t nelem,size_t elsize);

void *calloc(size_t nelem,size_t elsize) {
    char* fail_num = getenv("CALLOC_FAIL");
    if (fail_num != NULL){
        ++global_counts.calloc;
        char *num;
        num = strtok(fail_num,",");
        while(num != NULL){
            if (atol(fail_num) == global_counts.calloc){
                return NULL;
            }
            num = strtok(NULL,",");
        }    
    }

	// normal calloc
	orig_calloc_type orig_calloc;
	orig_calloc = (orig_calloc_type)dlsym(RTLD_NEXT,"calloc");
	return orig_calloc(nelem,elsize);
}
