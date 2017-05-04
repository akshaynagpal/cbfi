/*
*
* fputc wrapper
*
*/

#include "wrapper.h"

typedef int (*orig_fputc_type)(int c, FILE *stream);

int fputc(int c, FILE *stream){

    char* fail_nums = getenv("FPUTC_FAIL");

    if (fail_nums != NULL){
        ++global_counts.fputc;

        // Note: strtok requires the a char* or char[] 
        // that it can modify and const char* won't work
        char *num;
        // Should we use strtok_r which is thread safe?: 
        num = strtok(fail_nums,",");
        while(num != NULL) {
            if (atol(num) == global_counts.fputc) {
                errno = EACCES;
                return EOF;
            }
            num = strtok(NULL,",");
        }
    }

    
    orig_fputc_type orig_fputc;
    orig_fputc = (orig_fputc_type)dlsym(RTLD_NEXT, "fputc");
    return orig_fputc(c, stream);
}
