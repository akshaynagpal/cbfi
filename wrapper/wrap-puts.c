/*
*
* puts wrapper
*
*/

#include "wrapper.h"

typedef int (*orig_puts_type)(const char *s);

int puts(const char *s){
    char* fail_num = getenv("PUTS_FAIL");
    int error = 0; // set to -1 if call is to be failed
    unsigned int *numbers = NULL; // filled by parse function
    unsigned int i = 0, length = 0;    // size of numbers array of integers
    int original = btrace_has_gcov();   // check if called by gcov

    if (fail_num != NULL && original == 0){
        ++global_counts.puts;
        length = parse_fail_str(&numbers, fail_num);
        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.puts) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1) {
            errno = EBADF;
            return EOF;
        }
    }
    
    orig_puts_type orig_puts;
    orig_puts = (orig_puts_type)dlsym(RTLD_NEXT, "puts");
    return orig_puts(s);
}
