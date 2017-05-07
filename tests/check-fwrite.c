#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include "cbfi.h"

int main ()
{
   FILE *fp;
   int err;
   char str[] = "test string";

   fp = fopen( "file.txt" , "w" );
   err = fwrite(str , 1 , strlen(str) * sizeof(char), fp);
   assert(err == 0);    // assert nothing was written

   err = fwrite(str , 1 , strlen(str) * sizeof(char), fp);
   assert(err == 0);    // assert nothing was written 

   fclose(fp);
   return errno;
}