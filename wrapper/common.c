/**
 *
 * Common utility functions
 *
 */

#include "wrapper.h"
#include <assert.h>

void *custom_malloc(size_t size){
    // normal malloc
    orig_malloc_type orig_malloc;
    orig_malloc = (orig_malloc_type)dlsym(RTLD_NEXT,"malloc");
    return orig_malloc(size);
}

unsigned int parse_fail_str(unsigned int **numbers, const char *failstr) {
    unsigned int size = 0, i = 0;
    char *num = NULL;
    char *numstr = NULL;

    // assume null terminated string
    numstr = (char*)custom_malloc(sizeof(char) * (strlen(failstr)+1));
    strcpy(numstr, failstr);
    while(numstr[i] != '\0') {
        if (numstr[i]==',')
            size++;
        i++;
    }
    size += 1; // total integers to be parsed is 1 more than comma
    *numbers = (unsigned int*)custom_malloc(sizeof(unsigned int) * size);
    i = 0;
    num = strtok(numstr, ",");
    while (num != NULL && i < size) {
        (*numbers)[i] = atol(num); // fill array with integer
        i++;
        num = strtok(NULL, ","); // move to next token
    }
    free(numstr);
    return size;
}


int btrace_has_gcov(void) {
    int array_len = 20;
    void *array[array_len];
    int size_on_stack = backtrace(array, array_len);
    char* gcov_flush_string = "flush_gcov";
    char* bin_bash_string = "/bin/bash";
    char** backtrace_list = backtrace_symbols(array, size_on_stack);
    
    //backtrace_symbols_fd(array, size_on_stack, 1);

    int ret = 0;
    // check if gcov_flush is calling
    for (int i = 0; i < size_on_stack; i++)
    {
        if(strstr(backtrace_list[i], gcov_flush_string) != NULL ||
            strstr(backtrace_list[i], bin_bash_string) != NULL ){
            ret = 1;  // gcov flush is calling, so skip
            break;
        }
    }
    return ret;
}