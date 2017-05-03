#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

int main(){
	int x = chdir("..");
    assert(x == 0);
    return 0;
}