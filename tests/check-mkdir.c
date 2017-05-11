#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "cbfi.h"

int main(){
	int x = mkdir("testmakedir",077);
    if(x != 0)
    	printf("mkdir1 failed with error no:%d ",errno);
    int y = mkdir("testmakedir2",077);
    if(y!=0)
    	printf("mkdir2 failed with error no:%d ",errno);
    rmdir("testmakedir");
    rmdir("testmakedir2");
    return 0;

}