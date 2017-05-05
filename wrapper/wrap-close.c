/**
 *
 * close() wrapper
 *
 **/

#include "wrapper.h"

typedef int (*orig_close_type)(int fd);

int close(int fd){
    char* fail_num = getenv("CLOSE_FAIL");
    if (fail_num != NULL){
        ++global_counts.close;
        char *num;
        num = strtok(fail_num,",");
		while(num != NULL){
        	if (atol(fail_num) == global_counts.close){
            	return -1;
        	}
        	num = strtok(NULL,",");
        }
    }
    orig_close_type orig_close;
    orig_close = (orig_close_type)dlsym(RTLD_NEXT, "close");
    return orig_close(fd);
}
