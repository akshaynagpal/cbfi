#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdlib.h>

// struct to maintain counts of calls
typedef struct
{
    long malloc;
} call_counts;

// global counts of each call
static call_counts global_counts;

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
