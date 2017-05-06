/**
* 
* chown wrapper
*
**/

#include "wrapper.h"

typedef int (*orig_chown_type)(const char *path, uid_t owner, gid_t group);

int chown (const char *path, uid_t owner, gid_t group) {

    char* fail_num = getenv("CHOWN_FAIL");
    int error = 0; // set to -1 if call is to be failed
    unsigned int *numbers = NULL; // filled by parse function
    unsigned int i = 0, length = 0;    // size of numbers array of integers

    if (fail_num != NULL) {
        ++global_counts.chown;
        length = parse_fail_str(&numbers, fail_num);
        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.chown) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1) // check if call is to be failed
            return -1;
    }

    // normal chown
    orig_chown_type orig_chown;
    orig_chown = (orig_chown_type)dlsym(RTLD_NEXT,"chown");
    return orig_chown(path, owner, group);
}