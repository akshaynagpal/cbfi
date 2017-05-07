/**
 *
 * fopen() wrapper
 *
 **/

#include "wrapper.h"

// see wrapper.h for more info  on call_counts
call_counts global_counts;

// typedef for fopen
typedef FILE* (*orig_fopen_t)(const char *path, const char *mode);

FILE *fopen(const char *path, const char *mode){
    char* fail_num = getenv("FOPEN_FAIL");
    char* pre_string = "/dev/tty";
    char* gcda_ext = "gcda";
    int error = 0; // set to -1 if call is to be failed
    unsigned int *numbers = NULL; // filled by parse function
    unsigned int i = 0, length = 0;    // size of numbers array of integers
    int original = btrace_has_gcov();   // check if called by gcov



    // checking for inner calls to open function
    if (fail_num != NULL && original == 0 && strcmp(path,pre_string) != 0
         && strstr(path,gcda_ext)==NULL) {

        // increment count for failing attempt
        ++global_counts.fopen;
        // allocate numbers and store parsed integers
        length = parse_fail_str(&numbers, fail_num);

        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.fopen) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1){ // check if call is to be failed
            errno = EINVAL;
            return NULL;
        } 
            
    }

    //original function call
    orig_fopen_t orig_fopen;
    orig_fopen = (orig_fopen_t)dlsym(RTLD_NEXT, "fopen");
    return orig_fopen(path, mode);
}