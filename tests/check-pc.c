// test python wrapper

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "cbfi.h"

int main(int argc, char **argv) {
	int fd;
	int err, i;
	size_t len;
	char buffer[100];
	FILE *fp;
	char r = '\0';

	char *fname = "/home/kunal/Documents/secure-4995/cbfi/python-wrapper/playground/sample.txt";
	char *content = "Hello World";
	len = strlen(content) * sizeof(char);

	// open for writing
	fd = open(fname, O_WRONLY|O_CREAT, 0640);

	// write can crash if fd fails so no need for assert
	// write
	err = write(fd, content, len);
	assert(err != -1);	// assert no error occurred

	// close file
	err = close(fd);

	// open for reading
	fd = open(fname, O_RDONLY);
	assert(fd > -1);

	// read file
	err = read(fd, buffer, len);
	assert(err == len);	// assert successful read

	// close fd
	close(fd);

	for (i = 0; i < strlen(content); ++i)
		puts(content);

	// putc
	fp = fopen("sample.txt", "a+");
	// beginnig of file
	fseek(fp, SEEK_SET, 0);
	for (i = 0; i < 5; ++i) {
		r = getc(fp);
		assert(r != EOF);
		err = putc('a', fp);
		assert(err != EOF);
	}

	fclose(fp);

	return errno;
}