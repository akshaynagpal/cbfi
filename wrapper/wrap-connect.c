/**
* 
* connect wrapper
*
**/

#include "wrapper.h"

typedef int (*orig_connect_type)(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen){

	char* fail_num = getenv("CONNECT_FAIL");
    if (fail_num != NULL){
        ++global_counts.connect;
        char *num;
        num = strtok(fail_num,",");
        while(num != NULL){
            if (atol(fail_num) == global_counts.connect){
                return -1;
            }
            num = strtok(NULL,",");
        }

    }

    // normal connect
	orig_connect_type orig_connect;
	orig_connect = (orig_connect_type)dlsym(RTLD_NEXT,"connect");
	return orig_connect(sockfd, addr, addrlen);
    
}