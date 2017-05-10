/*
*
* putc wrapper
*
*/

#include "wrapper.h"

typedef int (*orig_putc_type)(int c, FILE *stream);

int putc(int c, FILE *stream){
    char* fail_num = getenv("PUTC_FAIL");
    unsigned int *numbers = NULL; // filled by parse function
    int original = btrace_has_gcov();   // check if called by gcov
    unsigned int length, i;
    int error = 0;

    if (fail_num != NULL && original == 0) {
        ++global_counts.putc;
        length = parse_fail_str(&numbers, fail_num);
        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.putc) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1) {
            errno = EBADF;
            return EOF;
        }
    }
    orig_putc_type orig_putc;
    orig_putc = (orig_putc_type)dlsym(RTLD_NEXT, "putc");
    return orig_putc(c, stream);
}
