/*
*
* fread wrapper
*
*/

#include "wrapper.h"

typedef size_t (*orig_fread_type)(void *ptr, size_t size, size_t nmemb,
    FILE * stream);

size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    char* fail_num = getenv("FREAD_FAIL");
    int error = 0; // set to -1 if call is to be failed
    unsigned int *numbers = NULL; // filled by parse function
    unsigned int i = 0, length = 0;    // size of numbers array of integers
    int original = btrace_has_gcov();   // check if called by gcov

    if (fail_num != NULL && original == 0){
        ++global_counts.fread;
        length = parse_fail_str(&numbers, fail_num);
        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.fread) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1) {
            errno = EBADF;
            return 0;   // fread returns short count on error
        }
    }
    
    orig_fread_type orig_fread;
    orig_fread = (orig_fread_type)dlsym(RTLD_NEXT, "fread");
    return orig_fread(ptr, size, nmemb, stream);
}
