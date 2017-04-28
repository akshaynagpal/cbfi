#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdlib.h>

typedef void* (*orig_malloc_type)(size_t size);

void *malloc(size_t size){
	// return NULL;
	orig_malloc_type orig_malloc;
	orig_malloc = (orig_malloc_type)dlsym(RTLD_NEXT,"malloc");
	return orig_malloc(size);
}
