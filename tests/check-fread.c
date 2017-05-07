#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <errno.h>
#include "cbfi.h"

int main()
{
   FILE *fp;
   char c[] = "test string";
   char buffer[100];
   size_t err;

   /* Open file for both reading and writing */
   fp = fopen("file.txt", "w+");

   /* Write data to the file */
   fwrite(c, strlen(c) + 1, 1, fp);

   /* Seek to the beginning of the file */
   fseek(fp, 0, SEEK_SET);

   /* Read and display data */
   err = fread(buffer, strlen(c)+1, 1, fp);
   assert(err == 0); // assert nothing was read
   fclose(fp);

   return errno;
}