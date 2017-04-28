/*
 * custom fopen wrapper
 *
 */

#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

// struct to maintain counts of calls
typedef struct
{
    long fopen;
    long printf;
} call_counts;

// global counts of each call
static call_counts global_counts;

// typedef for fopen
typedef FILE* (*orig_fopen_t)(const char *path, const char *mode);

FILE *fopen(const char *path, const char *mode){
    ++global_counts.fopen;
    char* fail_num = getenv("FOPEN_FAIL");
    if (fail_num != NULL && atol(fail_num) == global_counts.fopen)
        return NULL;
    orig_fopen_t orig_fopen;
    orig_fopen = (orig_fopen_t)dlsym(RTLD_NEXT, "fopen");
    return orig_fopen(path, mode);
}
