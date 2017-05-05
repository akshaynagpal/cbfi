#include <stdio.h>
#include <string.h>

int main ()
{
   const char src[50] = "http://www.google.com";
   char dest[50];

   printf("Before memcpy dest = %s\n", dest);
   memcpy(dest, src, strlen(src)+1);
   printf("After memcpy dest = %s\n", dest);
   
   return(0);
}