/**
 *
 * fgetc() wrapper
 *
 **/

#include "wrapper.h"

typedef int (*orig_fgetc_type)(FILE *stream);

int fgetc(FILE *stream){
    char* fail_num = getenv("FGETC_FAIL");
    if (fail_num != NULL){
        ++global_counts.fgetc;
        if (atol(fail_num) == global_counts.fgetc)
        	errno = ENOMEM; 
            exit(ENOMEM);
            return EOF;
    }
    orig_fgetc_type orig_fgetc;
    orig_fgetc = (orig_fgetc_type)dlsym(RTLD_NEXT, "fgetc");
    return orig_fgetc(stream);
}
