#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include "cbfi.h"

int main(){
	mkdir("testmakedir",077);
	printf("errno:%d \n",errno);
	assert(errno==0);
    mkdir("testmakedir2",077);
    printf("errno:%d \n",errno);
    assert(errno==0);
    opendir("testmakedir");
    printf("errno:%d \n",errno);
    assert(errno==0);
    opendir("testmakedir2");
    printf("errno:%d \n",errno);
    assert(errno==0);
    rmdir("testmakedir");
    assert(errno==0);
    rmdir("testmakedir2");
    assert(errno==0);
    return 0;
}