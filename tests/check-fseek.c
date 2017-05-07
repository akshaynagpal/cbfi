#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

int main()
{
   FILE *fp;
   char c[] = "test string";
   size_t err;

   /* Open file for both reading and writing */
   fp = fopen("file.txt", "w+");

   /* Write data to the file */
   fwrite(c, strlen(c) + 1, 1, fp);

   /* Seek to the beginning of the file */
   err = fseek(fp, 0, SEEK_SET);
   assert(err == -1); // assert nothing was read

   err = fseek(fp, 5, SEEK_SET);
   assert(err == -1);

   fclose(fp);

   return errno;
}