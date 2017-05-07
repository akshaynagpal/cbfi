/**
* 
* chdir wrapper
*
**/

#include "wrapper.h"

typedef int (*orig_chdir_type)(const char *path);

int chdir(const char *path){

	char* fail_num = getenv("CHDIR_FAIL");
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
        ++global_counts.chdir;
        // allocate numbers and store parsed integers
        length = parse_fail_str(&numbers, fail_num);

        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.chdir) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1) // check if call is to be failed
            return -1;
    }

    // normal chdir
	orig_chdir_type orig_chdir;
	orig_chdir = (orig_chdir_type)dlsym(RTLD_NEXT,"chdir");
	return orig_chdir(path);

}