#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "cbfi.h"

int main(){
    int* x = (int*)malloc(sizeof(int));
    assert(x != NULL);
    *x = 5;
    assert(*x == 5);
    /*int *x = (int*)malloc(sizeof(int));
    *x = 5;
    int *y = (int*)malloc(sizeof(int));
    *y = 5;*/
    return 0;
}
