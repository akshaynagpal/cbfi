/**
* 
* connect wrapper
*
**/

#include "wrapper.h"

typedef int (*orig_connect_type)(int sockfd, const struct sockaddr *addr, socklen_t addrlen);

int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen){

	char* fail_num = getenv("CONNECT_FAIL");
    int error = 0; // set to -1 if call is to be failed
    unsigned int *numbers = NULL; // filled by parse function
    unsigned int i = 0, length = 0;    // size of numbers array of integers
    int original = btrace_has_gcov();   // check if called by gcov

    // checking for inner calls to open function
    if (fail_num != NULL && original == 0) {

        // increment count for failing attempt
        ++global_counts.connect;
        // allocate numbers and store parsed integers
        length = parse_fail_str(&numbers, fail_num);

        // iterate over numbers array
        for (i = 0; i < length; i++) {
            if (numbers[i] == global_counts.connect) {
                error = -1;
                break;
            }
        }
        free(numbers); // release memory
        if (error == -1){ // check if call is to be failed
            errno = ECONNREFUSED;
            return -1;  
        }    
    }

    // normal connect
	orig_connect_type orig_connect;
	orig_connect = (orig_connect_type)dlsym(RTLD_NEXT,"connect");
	return orig_connect(sockfd, addr, addrlen);    
}