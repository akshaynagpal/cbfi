/**
 *
 * read wrapper
 *
 **/

#include "wrapper.h"

typedef ssize_t (*orig_read_type)(int filedes, void *buf, size_t nbyte);

ssize_t read(int filedes, void *buf, size_t nbyte) {
    char* fail_num = getenv("READ_FAIL");
    int error = 0; // set to -1 if call is to be failed
    unsigned int *numbers = NULL; // filled by parse function
    unsigned int i = 0, length = 0;    // size of numbers array of integers
    int original = btrace_has_gcov();   // check if called by gcov

    // checking for inner calls to read function
    if (fail_num != NULL && original == 0) {

        // increment count for failing attempt
        ++global_counts.read;
        // allocate numbers and store parsed integers
        length = parse_fail_str(&numbers, fail_num);

        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.read) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1) {
            errno = EBADF;
            return -1;
        }
    }
    orig_read_type orig_read;
    orig_read = (orig_read_type)dlsym(RTLD_NEXT, "read");
    return orig_read(filedes, buf, nbyte);
}
