/**
 *
 * open() wrapper
 *
 **/

#include "wrapper.h"

typedef int (*orig_open_type)(const char *pathname, int flags);

int open(const char *pathname, int flags){
    char* fail_num = getenv("OPEN_FAIL");
    if (fail_num != NULL){
        ++global_counts.open;
        if (atol(fail_num) == global_counts.open)
            return -1;
    }
    orig_open_type orig_open;
    orig_open = (orig_open_type)dlsym(RTLD_NEXT, "open");
    return orig_open(pathname, flags);
}
