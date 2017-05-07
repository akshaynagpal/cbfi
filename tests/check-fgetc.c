#include <stdio.h>
#include <errno.h>
#include "cbfi.h"

int main ()
{
   FILE *fp;
   int c;
   int count = 0;
  
   fp = fopen("file.txt","r");
   if(fp == NULL)
   {
      perror("Error in opening file");
      return(-1);
   }
   do
   {
      c = fgetc(fp);
      count++;
      if(c==EOF)
      {
         printf("\nerrno: %d\n",errno);
      }
      printf("%c", c);
   }while(count<9);
   fclose(fp);
   return(0);
}
