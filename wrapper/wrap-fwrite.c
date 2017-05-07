/*
*
* fwrite wrapper
*
*/

#include "wrapper.h"

typedef size_t (*orig_fwrite_type)(const void *ptr, size_t size, size_t nmemb,
    FILE *stream);

size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream) {
    char* fail_num = getenv("FWRITE_FAIL");
    int error = 0; // set to -1 if call is to be failed
    unsigned int *numbers = NULL; // filled by parse function
    unsigned int i = 0, length = 0;    // size of numbers array of integers
    int original = btrace_has_gcov();   // check if called by gcov

    if (fail_num != NULL && original == 0){
        ++global_counts.fwrite;
        length = parse_fail_str(&numbers, fail_num);
        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.fwrite) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1) {
            errno = EBADF;
            return 0;   // fwrite fails to write anything
        }
    }
    
    orig_fwrite_type orig_fwrite;
    orig_fwrite = (orig_fwrite_type)dlsym(RTLD_NEXT, "fwrite");
    return orig_fwrite(ptr, size, nmemb, stream);
}
