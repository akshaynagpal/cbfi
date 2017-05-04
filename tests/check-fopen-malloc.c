#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cbfi.h"

int main(){
    FILE *fp1;
    fp1=fopen("foo.txt","w+");
    assert(fp1!=NULL);
    fprintf(fp1,"hello world");
    int z = fclose(fp1);
    int *x = (int*)malloc(sizeof(int));
    *x = 5;
    int *y = (int*)malloc(sizeof(int));
    *y = 5;
    return 0;
}
