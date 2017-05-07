/**
 *
 * gets() wrapper
 *
 **/

#include "wrapper.h"

typedef char* (*orig_gets_type)(char *s);

char *gets(char *s) {
    // fail gets
    char* fail_num = getenv("GETS_FAIL");
    unsigned int *numbers = NULL; // filled by parse function
    int original = btrace_has_gcov();   // check if called by gcov
    unsigned int length, i;
    int error = 0;

    if (fail_num != NULL && original == 0) {
        ++global_counts.gets;
        length = parse_fail_str(&numbers, fail_num);
        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.gets) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1) {
            errno = ENOMEM;
            return NULL;
        }
    }

    orig_gets_type orig_gets;
    orig_gets = (orig_gets_type)dlsym(RTLD_NEXT, "gets");
    return orig_gets(s);
}
