#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include "cbfi.h"

int main ()
{
   FILE *fp;
   char str[100];
   char *ret;
  
   fp = fopen("file.txt","r");
   if(fp == NULL) 
   {
      perror("Error in opening file");
      return(-1);
   }

   ret = fgets(str, 60, fp);
   assert(ret == NULL); // check for fail

   fclose(fp);
   return errno;
}
