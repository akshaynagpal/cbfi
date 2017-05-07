/**
* 
* chdir wrapper
*
**/

#include "wrapper.h"

typedef int (*orig_chmod_type)(const char *path, mode_t  mode);

int chmod(const char *path, mode_t mode) {

    char* fail_num = getenv("CHMOD_FAIL");
    int error = 0; // set to -1 if call is to be failed
    unsigned int *numbers = NULL; // filled by parse function
    unsigned int i = 0, length = 0;    // size of numbers array of integers
    int original = btrace_has_gcov();   // check if called by gcov

    if (fail_num != NULL && original == 0) {
        ++global_counts.chmod;
        length = parse_fail_str(&numbers, fail_num);
        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.chmod) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1) // check if call is to be failed
            return -1;
    }

    // normal chmod
    orig_chmod_type orig_chdir;
    orig_chdir = (orig_chmod_type)dlsym(RTLD_NEXT,"chmod");
    return orig_chdir(path, mode);
}