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
    assert(x!=-1);
    int y = close(x);
    assert(y!=-1);
    int w = open("opentest.txt",O_RDONLY);
    assert(w!=-1);
    int z = close(w);
    assert(z!=-1);
    return 0;
}
