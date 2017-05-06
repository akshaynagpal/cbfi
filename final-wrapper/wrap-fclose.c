/**
 *
 * fclose() wrapper
 *
 **/

#include "wrapper.h"

typedef int (*orig_fclose_type)(FILE *stream);

int fclose(FILE *stream){
    char* fail_num = getenv("FCLOSE_FAIL");

    if (fail_num != NULL){
        ++global_counts.fclose;
    	char *num;
    	num = strtok(fail_num,",");
		while(num != NULL){
        	if (atol(fail_num) == global_counts.fclose){
            	return EOF;
        	}
        	num = strtok(NULL,",");
        }
    }
    orig_fclose_type orig_fclose;
    orig_fclose = (orig_fclose_type)dlsym(RTLD_NEXT, "fclose");
    return orig_fclose(stream);
}
