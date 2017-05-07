#include <stdio.h>
#include <assert.h>
#include "cbfi.h"

int main(){
    FILE *fp1;
    int ret;
    fp1=fopen("foo.txt","w+");
    ret = fputs("hello world 1", fp1);
    assert(ret == EOF);    // assert fputs failure

    ret = fputs("hello world 2", fp1);
    assert(ret == EOF);    // assert fputs failure

    fclose(fp1);
    return 0;
}
