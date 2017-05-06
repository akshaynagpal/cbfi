/**
 *
 * memcpy() wrapper NOT USING FOR NOW
 *
 **/

// #include "wrapper.h"

// typedef void* (*orig_memcpy_type)(void *dest, const void *src, size_t n);

// void* memcpy(void *dest, const void *src, size_t n) {
//     printf("here\n");
//     char* fail_num = getenv("MEMCPY_FAIL");
//     if (fail_num != NULL){
//         ++global_counts.memcpy;
//         char *num;
//         num = strtok(fail_num,",");
//         while(num != NULL){
//             if (atol(fail_num) == global_counts.memcpy){
//                 return NULL;
//             }
//             num = strtok(NULL,",");
//         }    
//     }

// 	// normal memcpy
// 	orig_memcpy_type orig_memcpy;
// 	orig_memcpy = (orig_memcpy_type)dlsym(RTLD_NEXT,"memcpy");
// 	return orig_memcpy(dest,src,n);
// }
