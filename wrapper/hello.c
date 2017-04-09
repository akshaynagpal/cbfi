#include <stdio.h>

int main(){
    int x = 2;
    FILE *fp;
    fp=fopen("foo.txt","w+");
    fprintf(fp,"hello world");
    fclose(fp);
    printf("hello world");
    return 0;
}