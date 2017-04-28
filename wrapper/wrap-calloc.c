#define _GNU_SOURCE

#include <dlfcn.h>
#include <stdlib.h>

typedef void* (*orig_calloc_type)(size_t nelem,size_t elsize);

void *calloc(size_t nelem,size_t elsize){
	// error calloc
	return NULL;

	// normal calloc
	orig_calloc_type orig_calloc;
	orig_calloc = (orig_calloc_type)dlsym(RTLD_NEXT,"calloc");
	return orig_calloc(nelem,elsize);
}
