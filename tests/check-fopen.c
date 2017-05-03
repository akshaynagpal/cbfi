#include <stdio.h>
#include <assert.h>
#include "cbfi.h"

int main(){
    FILE *fp1;
    fp1=fopen("foo.txt","w+");
    assert(fp1!=NULL);
    fprintf(fp1,"hello world");
    int y = fclose(fp1);
    assert(y!=EOF);
    return 0;
}
