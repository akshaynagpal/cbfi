/*
*
* fputc wrapper
*
*/

#include "wrapper.h"

typedef int (*orig_fputc_type)(int c, FILE *stream);

int fputc(int c, FILE *stream){
    char* fail_num = getenv("FPUTC_FAIL");
    unsigned int *numbers = NULL; // filled by parse function
    int original = btrace_has_gcov();   // check if called by gcov
    unsigned int length, i;
    int error = 0;

    if (fail_num != NULL && original == 0) {
        ++global_counts.fputc;
        length = parse_fail_str(&numbers, fail_num);
        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.fputc) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1) {
            errno = EACCES;
            return EOF;
        }
    }
    orig_fputc_type orig_fputc;
    orig_fputc = (orig_fputc_type)dlsym(RTLD_NEXT, "fputc");
    return orig_fputc(c, stream);
}
