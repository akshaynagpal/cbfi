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
    return 0;
}
