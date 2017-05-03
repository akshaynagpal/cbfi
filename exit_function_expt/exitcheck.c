#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
	exit(ENOMEM);
	printf("exiting here..\n");
	return 0;
}
