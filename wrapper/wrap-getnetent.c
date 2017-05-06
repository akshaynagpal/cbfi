/**
 *
 * wrapper for get network name
 *
 **/

#include "wrapper.h"

typedef struct netent* (*orig_getnetent_t)(void);

struct netent *getnetent(void) {
    char* fail_num = getenv("GETNETENT_FAIL");
    int error = 0; // set to -1 if call is to be failed
    unsigned int *numbers = NULL; // filled by parse function
    unsigned int i = 0, length = 0;  // size of numbers array of integers

    if (fail_num != NULL) {
        ++global_counts.dup2;
        length = parse_fail_str(&numbers, fail_num);
        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.dup2) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1) // check if call is to be failed
            return NULL; // this call returns NULL on error
    }

    //original function call
    orig_getnetent_t orig_getnetent;
    orig_getnetent = (orig_getnetent_t)dlsym(RTLD_NEXT, "getnetent");
    return orig_getnetent();
}