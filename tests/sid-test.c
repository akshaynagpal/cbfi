#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cbfi.h"

int main(){
    FILE *fp1;
    fp1=fopen("foo.txt","w+");
    fprintf(fp1,"hello world");
    int r = fputc('a',fp1);
    if (r == 'a') {
        r = fputc('b', fp1);
        if(r == 'b') {
            printf("Hola");
        }
    }
    flush_gcov();
    // int z = fclose(fp1);
    int *i = (int*)malloc(sizeof(int));
    if(i == NULL) {
        printf("NULL");
    } else {
        *i = 5;
        printf("%d",*i);
    }
    // int *j = (int*)malloc(sizeof(int));
    return 0;
}
