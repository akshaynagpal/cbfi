#include <stdio.h>
#include "cbfi.h"
#include <errno.h>

int main ()
{
	printf("%d\n",errno );
   FILE *fp;
   int ch;

   fp = fopen("file1.txt", "w+");
   for( ch = 33 ; ch <= 100; ch++ )
   {
      fputc(ch, fp);
   }
   fclose(fp);
   printf("%d\n",errno );
   return(0);
}