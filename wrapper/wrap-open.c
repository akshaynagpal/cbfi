/**
 *
 * open() wrapper
 *
 **/

#include "wrapper.h"

typedef int (*orig_open_type)(const char *pathname, int flags, mode_t mode);

int open(const char *pathname, int flags, mode_t mode){
    char* fail_num = getenv("OPEN_FAIL");
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
        ++global_counts.open;
        // allocate numbers and store parsed integers
        length = parse_fail_str(&numbers, fail_num);

        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.open) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1) // check if call is to be failed
            return -1;
    }
    orig_open_type orig_open;
    orig_open = (orig_open_type)dlsym(RTLD_NEXT, "open");
    return orig_open(pathname, flags, mode);
}
