#include <stdio.h>
//#include "cbfi.h"

int main(){
    int x = 2;
    FILE *fp1;
    fp1=fopen("foo.txt","w+");
    fprintf(fp1,"hello world");
    fclose(fp1);
    printf("hello world");
    return 0;
}
