#include <stdio.h>
#include <errno.h>
int main ()
{
   FILE *fp;
   int c;
   int n = 0;
  
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