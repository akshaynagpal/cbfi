/**
 *
 * lseek() wrapper
 *
 **/

#include "wrapper.h"

typedef off_t (*orig_lseek_type)(int fildes, off_t offset, int whence);

off_t lseek(int fildes, off_t offset, int whence) {
    char* fail_num = getenv("LSEEK_FAIL");
    int error = 0; // set to -1 if call is to be failed
    unsigned int *numbers = NULL; // filled by parse function
    unsigned int i = 0, length = 0;    // size of numbers array of integers
    int original = btrace_has_gcov();   // check if called by gcov

    // checking for inner calls to lseek function
    if (fail_num != NULL && original == 0) {

        // increment count for failing attempt
        ++global_counts.lseek;
        // allocate numbers and store parsed integers
        length = parse_fail_str(&numbers, fail_num);

        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.lseek) {
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
    orig_lseek_type orig_lseek;
    orig_lseek = (orig_lseek_type)dlsym(RTLD_NEXT, "lseek");
    return orig_lseek(fildes, offset, whence);
}
