#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include "cbfi.h"

int main ()
{
   char str[100],str2[100];

   gets(str);
   if(str == NULL){
      printf("gets 1 fail\n");
   }
   else{
      printf("gets 1 print: %s\n",str);
   }

   gets(str2);
   if(str2 == NULL){
      printf("gets 2 fail\n");
   }
   else{
      printf("gets 2 print: %s\n",str2);
   }
   return 0;
}
