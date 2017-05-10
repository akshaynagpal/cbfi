#include <stdio.h>
#include "cbfi.h"
#include <errno.h>
#include <assert.h>

int main ()
{
	FILE *fp;
   int err;

   fp = fopen("file1.txt", "w+");
   err = putc(65, fp);  // write A
   assert(err == EOF);  // EOF on error

   err = putc(66, fp);  // write A
   assert(err == EOF);  // EOF on error

   fclose(fp);
   return errno;
}