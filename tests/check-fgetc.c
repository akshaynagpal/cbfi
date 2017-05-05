#include <stdio.h>
#include <errno.h>
#include "cbfi.h"

int main ()
{
   FILE *fp;
   int c;
  
   fp = fopen("file.txt","r");
   if(fp == NULL) 
   {
      perror("Error in opening file");
      return(-1);
   }
   do
   {
      c = fgetc(fp);
      if( c==EOF )
      {
         break ;
      }
      printf("%c", c);
   }while(1);

   fclose(fp);
   return(0);
}
