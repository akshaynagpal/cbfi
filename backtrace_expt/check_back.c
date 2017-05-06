#define _GNU_SOURCE
#include <stdio.h>
#include <execinfo.h>
#include <stdlib.h>
#include <dlfcn.h>

void handler(char *caller) {
  void *array[10];
  size_t size;
  printf("Stack Trace Start for %s\n",caller);
  size = backtrace(array, 10);
  Dl_info info[size];
  for(int i=0;i <size; i++) {
	  dladdr(array[i],&info[i]);
	  if(&info[i] != NULL) {
	  	printf("Got it %s\n",info[i].dli_fname);
	  	printf("Got it %s\n",info[i].dli_sname);
	  }
	}
  backtrace_symbols(array, size);
  printf("Stack Trace End\n");
}

void gcov_flush() {
	handler("car()");
    printf("Continue Execution");
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