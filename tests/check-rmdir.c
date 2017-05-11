/**
 *
 * rmdir() testing
 *
 *
 **/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char const *argv[])
{
	int err = 0;
	char *dirname = "secret-dir";

	// create dir
	err = mkdir(dirname, 0777);
	assert(err == 0);

	// remove directory
	err = rmdir(dirname);
	assert(err == -1);

	// remove directory
	err = rmdir(dirname);
	assert(err == -1);

	return err;
}