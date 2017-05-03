/**
 *
 * fclose() wrapper
 *
 **/

#include "wrapper.h"

typedef int (*orig_fclose_type)(FILE *stream);

int fclose(FILE *stream){
    char* fail_num = getenv("FCLOSE_FAIL");
    if (fail_num != NULL){
        ++global_counts.fclose;
        if (atol(fail_num) == global_counts.fclose)
            return EOF;
    }
    orig_fclose_type orig_fclose;
    orig_fclose = (orig_fclose_type)dlsym(RTLD_NEXT, "fclose");
    return orig_fclose(stream);
}
