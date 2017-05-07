/*
*
* fputs wrapper
*
*/

#include "wrapper.h"

typedef int (*orig_fputs_type)(const char *s, FILE *stream);

int fputs(const char *s, FILE *stream){
    char* fail_num = getenv("FPUTS_FAIL");
    int error = 0; // set to -1 if call is to be failed
    unsigned int *numbers = NULL; // filled by parse function
    unsigned int i = 0, length = 0;    // size of numbers array of integers
    int original = btrace_has_gcov();   // check if called by gcov

    if (fail_num != NULL && original == 0){
        ++global_counts.fputs;
        length = parse_fail_str(&numbers, fail_num);
        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.fputs) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1) {
            errno = EPERM;
            return EOF;
        }
    }
    
    orig_fputs_type orig_fputs;
    orig_fputs = (orig_fputs_type)dlsym(RTLD_NEXT, "fputs");
    return orig_fputs(s, stream);
}
