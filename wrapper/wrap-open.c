/**
 *
 * open() wrapper
 *
 **/

#include "wrapper.h"
#include <string.h>

// see wrapper.h for more info  on call_counts
call_counts global_counts;

typedef int (*orig_open_type)(const char *pathname, int flags, mode_t mode);

int open(const char *pathname, int flags, mode_t mode){
    char* fail_num = getenv("OPEN_FAIL");
    char* pre_string = "/dev/tty";
    char* gcda_ext = "gcda";
    char* gcov_flush_string = "gcov_flush";
    int original = 0;
    void *array[10];
    int size_on_stack = backtrace(array,10);
    char** backtrace_list = backtrace_symbols(array,size_on_stack);
    
    // check if gcov_flush is calling
    for (int i = 0; i < size_on_stack; i++)
    {
        if(strstr(backtrace_list[i],gcov_flush_string)!=NULL){
            original = 1;  // gcov flush is calling, so skip to orig_malloc by setting original to 1
        }
    }

    // checking for inner calls to open function
    if (fail_num != NULL && original == 0 && strcmp(pathname,pre_string) != 0 && strstr(pathname,gcda_ext)==NULL){
        char *num;
        num = strtok(fail_num,",");
        while(num!=NULL){
            ++global_counts.open;
            if (atol(fail_num) == global_counts.open){
                return -1;
            }
        }
        num = strtok(NULL,",");
    }
    orig_open_type orig_open;
    orig_open = (orig_open_type)dlsym(RTLD_NEXT, "open");
    return orig_open(pathname, flags, mode);
}
