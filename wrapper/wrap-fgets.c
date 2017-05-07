/**
 *
 * fgets() wrapper
 *
 **/

#include "wrapper.h"

typedef char* (*orig_fgets_type)(char *s, int size, FILE *stream);

char *fgets(char *s, int size, FILE *stream) {
    // fail fgets
    char* fail_num = getenv("FGETS_FAIL");
    unsigned int *numbers = NULL; // filled by parse function
    int original = btrace_has_gcov();   // check if called by gcov
    unsigned int length, i;
    int error = 0;

    if (fail_num != NULL && original == 0) {
        ++global_counts.fgets;
        length = parse_fail_str(&numbers, fail_num);
        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.fgets) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1) {
            errno = ENOMEM;
            return NULL;
        }
    }

    orig_fgets_type orig_fgets;
    orig_fgets = (orig_fgets_type)dlsym(RTLD_NEXT, "fgets");
    return orig_fgets(s, size, stream);
}
