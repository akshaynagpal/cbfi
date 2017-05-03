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
    int x=open("testopen.txt",O_APPEND|O_CREAT);
    assert(x!=-1);
    int y = close(x);
    assert(y!=-1);
    return 0;
}