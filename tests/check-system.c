#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cbfi.h"

int main ()
{
   int x,y;
   x = system("pwd");
   if(x==-1){
   	printf("system call 1 failed\n");
   }
   y = system("pwd");
   if(y==-1){
   	printf("system call 2 failed\n");
   }
   return(0);
} 