/**
* 
* rmdir wrapper
*
**/

#include "wrapper.h"

typedef int (*orig_rmdir_type)(const char *path);

int rmdir(const char *path){

	char* fail_num = getenv("RMDIR_FAIL");
    int error = 0; // set to -1 if call is to be failed
    unsigned int *numbers = NULL; // filled by parse function
    unsigned int i = 0, length = 0;    // size of numbers array of integers
    int original = btrace_has_gcov();   // check if called by gcov
    
    // checking for inner calls to open function
    if (fail_num != NULL && original == 0) {

        // increment count for failing attempt
        ++global_counts.rmdir;
        // allocate numbers and store parsed integers
        length = parse_fail_str(&numbers, fail_num);

        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.rmdir) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1){
            errno = EACCES; // deny access
            return -1;
        }
    }

    // normal rmdir
	orig_rmdir_type orig_rmdir;
	orig_rmdir = (orig_rmdir_type)dlsym(RTLD_NEXT,"rmdir");
	return orig_rmdir(path);

}