/**
 *
 * wrapper for get network name
 *
 **/

#include "wrapper.h"

typedef struct netent* (*orig_getnetbyaddr_t)(uint32_t net, int type);

struct netent *getnetbyaddr(uint32_t net, int type) {
    char* fail_num = getenv("GETNETBYADDR_FAIL");
    int error = 0; // set to -1 if call is to be failed
    unsigned int *numbers = NULL; // filled by parse function
    unsigned int i = 0, length = 0;  // size of numbers array of integers

    if (fail_num != NULL) {
        ++global_counts.getnetbyaddr;
        length = parse_fail_str(&numbers, fail_num);
        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.getnetbyaddr) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1) // check if call is to be failed
            return NULL; // this call returns NULL on error
    }

    //original function call
    orig_getnetbyaddr_t orig_getnetbyaddr;
    orig_getnetbyaddr = (orig_getnetbyaddr_t)dlsym(RTLD_NEXT, "getnetbyaddr");
    return orig_getnetbyaddr(net, type);
}
