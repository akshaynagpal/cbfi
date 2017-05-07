#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include "cbfi.h"

int main(){
    int x=open("opentest1.txt",O_RDONLY);
    if(x==-1){
    	printf("open 1 failed\n");
    }
    int y = close(x);
    if(y==-1){
    	printf("close 1 failed\n");
    }
    int w = open("opentest.txt",O_RDONLY);
    if(w==-1){
    	printf("open 2 failed\n");	
    }
    int z = close(w);
    if(z==-1){
    	printf("close 2 failed\n");
    }
    return 0;
}
