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
    char* fail_nums = getenv("FOPEN_FAIL");

    if (fail_nums != NULL){
    printf("failing fopen");
        ++global_counts.fopen;
        // Note: strtok requires the a char* or char[] 
        // that it can modify and const char* won't work
        char *num; 
        num = strtok(fail_nums,",");
        while(num != NULL){
            if (atol(num) == global_counts.fopen)
                return NULL;
            num = strtok(NULL,",");
        }
    }

    //original function call
    orig_fopen_t orig_fopen;
    orig_fopen = (orig_fopen_t)dlsym(RTLD_NEXT, "fopen");
    return orig_fopen(path, mode);
}