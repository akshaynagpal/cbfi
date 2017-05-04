/**
 *
 * fgetc() wrapper
 *
 **/

#include "wrapper.h"

// see wrapper.h for more info  on call_counts
call_counts global_counts;

typedef int (*orig_fgetc_type)(FILE *stream);

int fgetc(FILE *stream){
    char* fail_num = getenv("FGETC_FAIL");
    if (fail_num != NULL){
        ++global_counts.fgetc;
        if (atol(fail_num) == global_counts.fgetc)
        	errno = ENOMEM;
            return EOF;
    }
    orig_fgetc_type orig_fgetc;
    orig_fgetc = (orig_fgetc_type)dlsym(RTLD_NEXT, "fgetc");
    return orig_fgetc(stream);
}
