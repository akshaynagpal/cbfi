/**
 *
 * fprintf() wrapper
 *
 **/

#include "wrapper.h"

typedef int (*orig_fprintf_type)(FILE *stream, const char *format, ...);

int fprintf(FILE *stream, const char *format, ...){
    // ... argument list
    char* fail_num = getenv("FPRINTF_FAIL");
    int error = 0, done = 0; // set to -1 if call is to be failed
    unsigned int *numbers = NULL; // filled by parse function
    unsigned int i = 0, length = 0;    // size of numbers array of integers
    int original = btrace_has_gcov();   // check if called by gcov
    
    if (fail_num != NULL && original == 0) {
            ++global_counts.fprintf;
            length = parse_fail_str(&numbers, fail_num);
            // iterate over numbers array
            for (i = 0; i < length; i++) {
                if (numbers[i] == global_counts.fprintf) {
                    error = -1;
                    break;
                }
            }
            free(numbers); // release memory
            if (error == -1)
                return -1;
        }

    va_list arg;
    va_start (arg, format);
    done = vfprintf (stream,format, arg);
    va_end (arg);
    return done;
}
