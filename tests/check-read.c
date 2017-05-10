#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "cbfi.h"

int main(){
    int fd, err;
    char buf[100];
    char *str = "sample string";
    size_t len = strlen(str) * sizeof(char);

    fd = open("opentest1.txt",O_RDWR);
    err = write(fd, str, len);
    assert(err == len);	// ensure write

    // seek start of file
    err = lseek(fd, SEEK_SET, 0);
    err = read(fd, buf, len);
    assert(err == -1);

    // seek start of file
    err = lseek(fd, SEEK_SET, 0);
    err = read(fd, buf, len);
    assert(err == -1);

    close(fd);
    return errno;
}
