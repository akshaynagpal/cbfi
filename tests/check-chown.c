#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/stat.h>
#include "cbfi.h"

// run this with sudo command

int main(){
    // uid = 0 and gid = 0 correspond to root
    int x = chown("foo.txt", 0, 0);
    assert(x == -1); // fail 1

    // change back to normal user uid and gid
    x = chown("foo.txt", 1000, 1000);
    assert(x == -1); // fail 2
    return errno;
}