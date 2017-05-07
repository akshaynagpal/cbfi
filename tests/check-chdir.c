#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "cbfi.h"

int main(){
	int x = chdir("..");
    if(x != 0)
    	printf("chdir1 failed\n");
    int y = chdir("..");
    if(y!=0)
    	printf("chdir2 failed\n");
    return 0;
}