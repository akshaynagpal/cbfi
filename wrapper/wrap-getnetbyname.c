/**
 *
 * wrapper for get network name
 *
 **/

#include "wrapper.h"

typedef struct netent* (*orig_getnetbyname_t)(const char *name);

struct netent *getnetbyname(const char *name) {
    char* fail_num = getenv("GETNETBYNAME_FAIL");
    int error = 0; // set to -1 if call is to be failed
    unsigned int *numbers = NULL; // filled by parse function
    unsigned int i = 0, length = 0;  // size of numbers array of integers
    int original = btrace_has_gcov();   // check if called by gcov

    if (fail_num != NULL && original == 0) {
        ++global_counts.getnetbyname;
        length = parse_fail_str(&numbers, fail_num);
        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.getnetbyname) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1) // check if call is to be failed
            return NULL; // this call returns NULL on error
    }

    //original function call
    orig_getnetbyname_t orig_getnetbyname;
    orig_getnetbyname = (orig_getnetbyname_t)dlsym(RTLD_NEXT, "getnetbyname");
    return orig_getnetbyname(name);
}
