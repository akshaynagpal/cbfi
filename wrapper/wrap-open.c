/**
 *
 * open() wrapper
 *
 **/

#include "wrapper.h"

typedef int (*orig_open_type)(const char *pathname, int flags);

int open(const char *pathname, int flags){
    char* fail_num = getenv("OPEN_FAIL");
    char* pre_string = "/dev/tty";
    char* gcda_ext = ".gcda";
    if (fail_num != NULL && strcmp(pathname,pre_string) != 0 && strstr(pathname,gcda_ext)==NULL){ // avoiding inner calls to open function
        ++global_counts.open;
        if (atol(fail_num) == global_counts.open)
            return -1;
    }
    orig_open_type orig_open;
    orig_open = (orig_open_type)dlsym(RTLD_NEXT, "open");
    return orig_open(pathname, flags);
}
