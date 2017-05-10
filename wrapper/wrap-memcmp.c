/**
 *
 * memcmp wrapper
 *
 **/

#include "wrapper.h"

typedef int (*orig_memcmp_type)(const void *s1, const void *s2, size_t n);

int memcmp(const void *s1, const void *s2, size_t n) {
    char* fail_num = getenv("MEMCMP_FAIL");
    int error = 0; // set to -1 if call is to be failed
    unsigned int *numbers = NULL; // filled by parse function
    unsigned int i = 0, length = 0;    // size of numbers array of integers
    int original = btrace_has_gcov();   // check if called by gcov

    // checking for inner calls to memcmp function
    if (fail_num != NULL && original == 0) {

        // increment count for failing attempt
        ++global_counts.memcmp;
        // allocate numbers and store parsed integers
        length = parse_fail_str(&numbers, fail_num);

        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.memcmp) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1) // check if call is to be failed
            return global_counts.memcmp;
    }
    orig_memcmp_type orig_memcmp;
    orig_memcmp = (orig_memcmp_type)dlsym(RTLD_NEXT, "memcmp");
    return orig_memcmp(s1, s2, n);
}
