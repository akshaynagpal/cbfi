/**
* 
* fork wrapper
*
**/

#include "wrapper.h"

typedef pid_t (*orig_fork_type)(void);

pid_t fork(void) {

    char* fail_num = getenv("FORK_FAIL");
    int error = 0; // set to -1 if call is to be failed
    unsigned int *numbers = NULL; // filled by parse function
    unsigned int i = 0, length = 0;    // size of numbers array of integers
    int original = btrace_has_gcov();   // check if called by gcov

    if (fail_num != NULL && original == 0) {
        ++global_counts.fork;
        length = parse_fail_str(&numbers, fail_num);
        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.fork) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1) {
            errno = EPERM;
            return -1;
        }
    }

    // normal fork
    orig_fork_type orig_fork;
    orig_fork = (orig_fork_type)dlsym(RTLD_NEXT,"fork");
    return orig_fork();
}