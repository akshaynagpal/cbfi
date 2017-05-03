/**
* 
* chdir wrapper
*
**/

#include "wrapper.h"

typedef int (*orig_chdir_type)(const char *path);

int chdir(const char *path){

	char* fail_num = getenv("CHDIR_FAIL");
    if (fail_num != NULL){
        ++global_counts.chdir;
        if (atol(fail_num) == global_counts.chdir)
            return -1;
    }

    // normal chdir
	orig_chdir_type orig_chdir;
	orig_chdir = (orig_chdir_type)dlsym(RTLD_NEXT,"chdir");
	return orig_chdir(path);

}