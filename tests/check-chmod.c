#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/stat.h>
#include "cbfi.h"

int main(){
    int x = chmod("foo.txt", S_IRUSR | S_IWUSR | S_IXUSR);
    assert(x == -1); // fail 1
    x = chmod("foo.txt", S_IRUSR | S_IWUSR);
    assert(x == -1); // fail 2
    return 0;
}