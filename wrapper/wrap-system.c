/**
 *
 * system() wrapper
 *
 **/

#include "wrapper.h"

typedef int (*orig_system_type)(const char *command);

int system(const char *command) {
    // fail gets
    char* fail_num = getenv("SYSTEM_FAIL");
    unsigned int *numbers = NULL; // filled by parse function
    int original = btrace_has_gcov();   // check if called by gcov
    unsigned int length, i;
    int error = 0;

    if (fail_num != NULL && original == 0) {
        ++global_counts.system;
        length = parse_fail_str(&numbers, fail_num);
        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.system) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1) {
            return -1;
        }
    }

    orig_system_type orig_system;
    orig_system = (orig_system_type)dlsym(RTLD_NEXT, "system");
    return orig_system(command);
}
