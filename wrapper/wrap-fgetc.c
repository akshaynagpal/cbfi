/**
 *
 * fgetc() wrapper
 *
 **/

#include "wrapper.h"

typedef int (*orig_fgetc_type)(FILE *stream);

int fgetc(FILE *stream){
    char* fail_num = getenv("FGETC_FAIL");
    int error = 0; // set to -1 if call is to be failed
    unsigned int *numbers = NULL; // filled by parse function
    unsigned int i = 0, length = 0;    // size of numbers array of integers
    int original = btrace_has_gcov();   // check if called by gcov

    // checking for inner calls to open function
    if (fail_num != NULL && original == 0){
        // increment count for failing attempt
        ++global_counts.fgetc;
        // allocate numbers and store parsed integers
        length = parse_fail_str(&numbers, fail_num);

        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.fgetc) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1){ // check if call is to be failed
            errno = ENOMEM;
            return EOF;
        }
    }

    orig_fgetc_type orig_fgetc;
    orig_fgetc = (orig_fgetc_type)dlsym(RTLD_NEXT, "fgetc");
    return orig_fgetc(stream);
}