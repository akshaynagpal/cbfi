/**
 *
 * malloc wrapper
 *
 **/

#include "wrapper.h"

typedef void* (*orig_malloc_type)(size_t size);

void *malloc(size_t size){
	char* fail_num = getenv("MALLOC_FAIL");
    if (fail_num != NULL && atol(fail_num) == global_counts.malloc)
        return NULL;

    // normal malloc
	orig_malloc_type orig_malloc;
	orig_malloc = (orig_malloc_type)dlsym(RTLD_NEXT,"malloc");
	return orig_malloc(size);
}
