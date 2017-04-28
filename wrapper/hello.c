#include <stdio.h>

void flush_gcov(){
    __gcov_flush();
}

int main(){
    int x = 2;
    FILE *fp;
    fp=fopen("foo.txt","w+");
    fprintf(fp,"hello world");
    fclose(fp);
    printf("hello world");
    return 0;
}
