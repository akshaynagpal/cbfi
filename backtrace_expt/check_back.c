#define _GNU_SOURCE
#include <stdio.h>
#include <execinfo.h>
#include <stdlib.h>
#include <dlfcn.h>

void handler(char *caller) {
  void* p = __builtin_return_address(0);
  Dl_info info;
  dladdr(p,&info);
  if(&info != NULL) {
  	fprintf(stdout,"Got it %s\n",info.dli_fname);
  	fprintf(stdout,"Got it %s\n",info.dli_sname);
  }
  p = __builtin_return_address(1);
  dladdr(p,&info);
  if(&info != NULL) {
  	fprintf(stdout,"Got it %s\n",info.dli_fname);
  	fprintf(stdout,"Got it %s\n",info.dli_sname);
  }
  p = __builtin_return_address(2);
  dladdr(p,&info);
  if(&info != NULL) {
  	fprintf(stdout,"Got it %s\n",info.dli_fname);
  	fprintf(stdout,"Got it %s\n",info.dli_sname);
  }

  int *i = malloc(sizeof(int));
  if(i == NULL){
	printf("I null");
  } else {
	printf("I not null\n");
  }
}

void gcov_flush() {
	handler("car()");
    //printf("Continue Execution");
}

void car() {
    gcov_flush();
}
void baz() {car(); }
void bar() { baz(); }
void foo() { bar(); }

int main(int argc, char **argv) {
  foo(); 
}