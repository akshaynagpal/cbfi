/**
 *
 * fclose() wrapper
 *
 **/

#include "wrapper.h"

typedef int (*orig_fclose_type)(FILE *stream);

int fclose(FILE *stream){
    char* fail_num = getenv("FCLOSE_FAIL");
    int error = 0; // set to -1 if call is to be failed
    unsigned int *numbers = NULL; // filled by parse function
    unsigned int i = 0, length = 0;    // size of numbers array of integers
    int original = btrace_has_gcov();   // check if called by gcov

    if (fail_num != NULL && original == 0) {

        // increment count for failing attempt
        ++global_counts.fclose;
        // allocate numbers and store parsed integers
        length = parse_fail_str(&numbers, fail_num);

        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.fclose) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1) // check if call is to be failed
            return EOF;
    }
    orig_fclose_type orig_fclose;
    orig_fclose = (orig_fclose_type)dlsym(RTLD_NEXT, "fclose");
    return orig_fclose(stream);
}
