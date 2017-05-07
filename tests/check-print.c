#include <stdio.h>
#include "cbfi.h"

int main(){
    int x = 2;
    char a = 'a';
    char* str = "array";
    int y = printf("hello world%d%c%s\n",x,a,str);
    printf("PRINTF VALUE:%d\n",y);
    printf("%d\n",x);
    return 0;
}
