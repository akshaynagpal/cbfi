/*
*
* kill wrapper
*
*/

#include "wrapper.h"

typedef size_t (*orig_kill_type)(pid_t pid, int sig);

int kill(pid_t pid, int sig) {
    char* fail_num = getenv("KILL_FAIL");
    int error = 0; // set to -1 if call is to be failed
    unsigned int *numbers = NULL; // filled by parse function
    unsigned int i = 0, length = 0;    // size of numbers array of integers
    int original = btrace_has_gcov();   // check if called by gcov

    if (fail_num != NULL && original == 0){
        ++global_counts.kill;
        length = parse_fail_str(&numbers, fail_num);
        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.kill) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1) {
            errno = EPERM;
            return -1;   // kill returns short count on error
        }
    }
    
    orig_kill_type orig_kill;
    orig_kill = (orig_kill_type)dlsym(RTLD_NEXT, "kill");
    return orig_kill(pid, sig);
}
