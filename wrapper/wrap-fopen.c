/*
 * custom fopen wrapper
 *
 */

#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>

//
typedef FILE* (*orig_fopen_t)(const char *path, const char *mode);

FILE *fopen(const char *path, const char *mode){
    fprintf(stdout, "WRAPPER FOPEN CALLED\n");
    orig_fopen_t orig_fopen;
    orig_fopen = (orig_fopen_t)dlsym(RTLD_NEXT, "fopen");
    return orig_fopen(path, mode);
    // return NULL;
}
