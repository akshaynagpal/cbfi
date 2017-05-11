#include <dlfcn.h>
#include <stdio.h>
#include <errno.h>
#include <assert.h>
#include <stdarg.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <execinfo.h>
#include <netdb.h>
#include <stdarg.h>
#include <dirent.h>
#include <sys/stat.h>
#include "cbfi.h"

int main(int argc, char const *argv[])
{
	FILE *fp;
	FILE *fp2;
	int x,y,z,w;
	char str[] = "test string";
	char c[] = "test string";
   	char buffer[100];
   	size_t a;

   	for (int i = 0; i < 2; ++i)
   	{
   		fp = fopen("/home/akshay/Desktop/playground/inputfile.txt","w");
		assert(fp!=NULL);
		x = fwrite(str , 1 , strlen(str) * sizeof(char), fp);
		assert(x>0);

		fclose(fp);

		fp2 = fopen("/home/akshay/Desktop/playground/inputfile2.txt","w+");
		
		y = fputs("hello world 1", fp2);
		assert(y!=EOF);

		w = fgetc(fp2);
		assert(errno == 0);

		z = fputc('x', fp2);
		assert(z!=EOF);

		fclose(fp2);

		fp = fopen("/home/akshay/Desktop/playground/inputfile.txt","r");
		a = fread(buffer, strlen(c), 1, fp);
		assert(a!=0);
		fclose(fp);
   	}

	return 0;
}