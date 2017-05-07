#include <stdio.h>
#include <assert.h>
#include "cbfi.h"

int main(){
    FILE *fp1;
    int ret;
    fp1=fopen("foo.txt","w+");
    ret = fprintf(fp1,"hello world 1");
    assert(ret < 0);    // assert fprintf failure

    ret = fprintf(fp1,"hello world 2");
    assert(ret < 0);    // assert fprintf failure

    fclose(fp1);
    return 0;
}
