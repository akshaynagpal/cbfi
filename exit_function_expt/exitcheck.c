#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	printf("exiting here..\n");
	exit(EIO);
	return 0;
}