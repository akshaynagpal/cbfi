#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include "cbfi.h"

int main(){
	int x = chdir("..");
    assert(x == 0);
    return 0;
}