#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include "cbfi.h"

int main(){
    int ret;

    ret = puts("hello world 1");
    assert(ret == EOF);    // assert puts failure

    ret = puts("hello world 2");
    assert(ret == EOF);    // assert puts failure
    return errno;
}
