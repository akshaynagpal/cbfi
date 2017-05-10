/**
 *
 * memcpy wrapper
 *
 * memcpy does not specifies any error, so we just
 * return back the dest pointer without copying any data
 * to evaluate how the program behaves in this scenario
 * This overlaps with the undefined behaviour of memcpy
 * on overlapping dest and src
 *
 **/

#include "wrapper.h"

typedef void* (*orig_memcpy_type)(void *dest, const void *src, size_t n);

void* memcpy(void *dest, const void *src, size_t n) {
    char* fail_num = getenv("MEMCPY_FAIL");
    int error = 0; // set to -1 if call is to be failed
    unsigned int *numbers = NULL; // filled by parse function
    unsigned int i = 0, length = 0;    // size of numbers array of integers
    int original = btrace_has_gcov();   // check if called by gcov

    // checking for inner calls to memcpy function
    if (fail_num != NULL && original == 0) {

        // increment count for failing attempt
        ++global_counts.memcpy;
        // allocate numbers and store parsed integers
        length = parse_fail_str(&numbers, fail_num);

        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.memcpy) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1) // check if call is to be failed
            return dest;
    }
    orig_memcpy_type orig_memcpy;
    orig_memcpy = (orig_memcpy_type)dlsym(RTLD_NEXT, "memcpy");
    return orig_memcpy(dest, src, n);
}
