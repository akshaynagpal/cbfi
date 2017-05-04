/*
*
* fputc wrapper
*
*/

#include "wrapper.h"

typedef int (*orig_fputc_type)(int c, FILE *stream);

int fputc(int c, FILE *stream){
    char* fail_num = getenv("FPUTC_FAIL");
    if (fail_num != NULL){
        ++global_counts.fputc;
        if (atol(fail_num) == global_counts.fputc)
        	errno = EACCES;
            return EOF;
    }
    orig_fputc_type orig_fputc;
    orig_fputc = (orig_fputc_type)dlsym(RTLD_NEXT, "fputc");
    return orig_fputc(c, stream);
}