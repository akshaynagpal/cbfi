/**
* 
* dup wrapper
*
**/

#include "wrapper.h"

typedef int (*orig_dup_type)(int oldfd);

int dup(int oldfd) {

    char* fail_num = getenv("DUP_FAIL");
    int error = 0; // set to -1 if call is to be failed
    unsigned int *numbers = NULL; // filled by parse function
    unsigned int i = 0, length = 0;    // size of numbers array of integers
    int original = btrace_has_gcov();   // check if called by gcov

    if (fail_num != NULL && original == 0) {
        ++global_counts.dup;
        length = parse_fail_str(&numbers, fail_num);
        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.dup) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1) // check if call is to be failed
            return -1;
    }

    // normal dup
    orig_dup_type orig_dup;
    orig_dup = (orig_dup_type)dlsym(RTLD_NEXT,"dup");
    return orig_dup(oldfd);
}