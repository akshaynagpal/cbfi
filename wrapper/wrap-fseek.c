/*
*
* fseek wrapper
*
*/

#include "wrapper.h"

typedef int (*orig_fseek_type)(FILE *stream, long offset, int whence);

int fseek(FILE *stream, long offset, int whence) {
    char* fail_num = getenv("FSEEK_FAIL");
    int error = 0; // set to -1 if call is to be failed
    unsigned int *numbers = NULL; // filled by parse function
    unsigned int i = 0, length = 0;    // size of numbers array of integers
    int original = btrace_has_gcov();   // check if called by gcov

    if (fail_num != NULL && original == 0){
        ++global_counts.fseek;
        length = parse_fail_str(&numbers, fail_num);
        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.fseek) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1) {
            errno = EBADF;  // stream unvailable
            return -1;   // fseek returns short count on error
        }
    }
    
    orig_fseek_type orig_fseek;
    orig_fseek = (orig_fseek_type)dlsym(RTLD_NEXT, "fseek");
    return orig_fseek(stream, offset, whence);
}
