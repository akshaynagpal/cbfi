#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdlib.h>

// struct to maintain counts of calls
typedef struct
{
    long calloc;
} call_counts;

// global counts of each call
static call_counts global_counts;

typedef void* (*orig_calloc_type)(size_t nelem,size_t elsize);

void *calloc(size_t nelem,size_t elsize){
	char* fail_num = getenv("CALLOC_FAIL");
    if (fail_num != NULL && atol(fail_num) == global_counts.calloc)
        return NULL;

	// normal calloc
	orig_calloc_type orig_calloc;
	orig_calloc = (orig_calloc_type)dlsym(RTLD_NEXT,"calloc");
	return orig_calloc(nelem,elsize);
}
