#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <sys/stat.h>
#include "cbfi.h"
#include <errno.h>

int main(){
	//Checking chdir
	int x = chdir("..");
	assert(x==0);
    int y = chdir("..");
    assert(y==0);
    //Checking chmod
    char mode1[] = "0700";
    char mode2[] = "0400";
    int j;
    j = strtol(mode1, 0, 8);
    int a = chmod("/home/siddharth/Desktop/foo.txt", j);
    assert(a != -1); // fail 1
    j = strtol(mode2, 0, 8);
    a = chmod("/home/siddharth/Desktop/foo.txt", j);
    assert(a != -1); // fail 2
    //Checking chown
    int b = chown("/home/siddharth/Desktop/foo.txt", 0, 0); // uid = 0 and gid = 0 correspond to root
    assert(b != -1); // fail 1
    b = chown("/home/siddharth/Desktop/foo.txt", 1000, 1000); // change back to normal user uid and gid
    assert(b != -1); // fail 2
    return 0;
}