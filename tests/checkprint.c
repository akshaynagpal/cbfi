#include <stdio.h>

int main(){
    int x = 2;
    char a = 'a';
    char* str = "array";
    int y = printf("hello world%d%c%s",x,a,str);
    printf("PRINTF VALUE:%d\n",y);
    return 0;
}
