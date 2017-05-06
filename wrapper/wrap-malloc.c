/**
 *
 * malloc() wrapper NOT USING AS OF NOW
 *
 **/

// #include "wrapper.h"

// typedef void* (*orig_malloc_type)(size_t size);

// void *malloc(size_t size){
// 	int original = 0;
// 	char* fail_num = getenv("MALLOC_FAIL");
// 	void *array[10];
//   	size_t size1;
// 	size1 = backtrace(array, 10);
//   	Dl_info info[size1];
  	
//   	// check if gcov_flush is calling
//   	for(int i=0;i <size1; i++) {
// 	  dladdr(array[i],&info[i]);
// 	  if(&info[i] != NULL && strstr(info[i].dli_sname,"gcov_flush")!=NULL) {
// 	  	original = 1; // gcov flush is calling, so skip to orig_malloc by setting original to 1
// 	  }
// 	}

//     if (fail_num != NULL && original==0){
//     	++global_counts.malloc;
//     	char *num;
// 		num = strtok(fail_num,",");
// 		while(num != NULL){
// 			if (atol(num) == global_counts.malloc)
//             	return NULL;
// 			num = strtok(NULL,",");
// 		}
//     }
    
//     // normal malloc
// 	orig_malloc_type orig_malloc;
// 	orig_malloc = (orig_malloc_type)dlsym(RTLD_NEXT,"malloc");
// 	return orig_malloc(size);
// }