/**
 *
 * fopen() wrapper
 *
 **/

#include "wrapper.h"

// see wrapper.h for more info  on call_counts
call_counts global_counts;

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
