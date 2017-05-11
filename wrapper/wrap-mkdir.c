/**
 *
 * mkdir() wrapper
 *
 **/

#include "wrapper.h"

// typedef for mkdir
typedef int (*orig_mkdir_t)(const char *pathname, mode_t mode);

int mkdir(const char *pathname, mode_t mode){
    char* fail_num = getenv("MKDIR_FAIL");
    char* pre_string = "/dev/tty";
    char* gcda_ext = "gcda";
    int error = 0; // set to -1 if call is to be failed
    unsigned int *numbers = NULL; // filled by parse function
    unsigned int i = 0, length = 0;    // size of numbers array of integers
    int original = btrace_has_gcov();   // check if called by gcov



    // checking for inner calls to open function
    if (fail_num != NULL && original == 0 && strcmp(pathname,pre_string) != 0
         && strstr(pathname,gcda_ext)==NULL) {

        // increment count for failing attempt
        ++global_counts.mkdir;
        // allocate numbers and store parsed integers
        length = parse_fail_str(&numbers, fail_num);

        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.mkdir) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1){ // check if call is to be failed
            errno = EACCES;
            return -1;
        } 
            
    }

    //original function call
    orig_mkdir_t orig_mkdir;
    orig_mkdir = (orig_mkdir_t)dlsym(RTLD_NEXT, "mkdir");
    return orig_mkdir(pathname, mode);
}