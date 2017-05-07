/**
 *
 * system() wrapper
 *
 **/

#include "wrapper.h"

typedef DIR* (*orig_opendir_type)(const char *name);

DIR* opendir(const char *name) {
    // fail gets
    char* fail_num = getenv("OPENDIR_FAIL");
    unsigned int *numbers = NULL; // filled by parse function
    int original = btrace_has_gcov();   // check if called by gcov
    unsigned int length, i;
    int error = 0;

    if (fail_num != NULL && original == 0) {
        ++global_counts.opendir;
        length = parse_fail_str(&numbers, fail_num);
        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.opendir) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1) {
            errno = ENFILE;
            return NULL;
        }
    }

    orig_opendir_type orig_opendir;
    orig_opendir = (orig_opendir_type)dlsym(RTLD_NEXT, "opendir");
    return orig_opendir(name);
}
