/**
 *
 * fileno() wrapper
 *
 **/

#include "wrapper.h"

typedef int (*orig_fileno_type)(FILE *stream);

int fileno(FILE *stream){
    char* fail_num = getenv("FILENO_FAIL");
    int error = 0; // set to -1 if call is to be failed
    unsigned int *numbers = NULL; // filled by parse function
    unsigned int i = 0, length = 0;    // size of numbers array of integers
    int original = btrace_has_gcov();   // check if called by gcov

    // checking for inner calls to open function
    if (fail_num != NULL && original == 0){
        // increment count for failing attempt
        ++global_counts.fileno;
        // allocate numbers and store parsed integers
        length = parse_fail_str(&numbers, fail_num);

        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.fileno) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1){ // check if call is to be failed
            errno = EBADF;
            return -1;
        }
    }

    orig_fileno_type orig_fileno;
    orig_fileno = (orig_fileno_type)dlsym(RTLD_NEXT, "fileno");
    return orig_fileno(stream);
}