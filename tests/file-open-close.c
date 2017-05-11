#include <stdio.h>
#include <assert.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "cbfi.h"

int main(){
    FILE *fp1;
    FILE *fp2;
    int i;
    
    fp1 = fopen("/home/siddharth/Desktop/foo.txt","w+");
    assert(fp1 != NULL);
    i = fclose(fp1);
    assert(i == 0);

    fp2 = fopen("/home/siddharth/Desktop/foo.txt","w+");
    assert(fp2 != NULL);
    i = fclose(fp2);
    assert(i == 0);

    int x = open("/home/siddharth/Desktop/foo.txt", O_RDONLY);
    assert(x != -1);
    int y = close(x);
    assert(y == 0);

    x = open("/home/siddharth/Desktop/foo.txt", O_RDONLY);
    assert(x != -1);
    y = close(x);
    assert(y == 0);
    
    return 0;
}
