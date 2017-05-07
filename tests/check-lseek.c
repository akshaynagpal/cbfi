#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <assert.h>
#include <unistd.h>
#include "cbfi.h"

int main(){
    int fd, err;
    fd = open("opentest1.txt",O_RDONLY);
    err = lseek(fd, SEEK_SET, 0);
    assert(err == -1);

    err = lseek(fd, SEEK_SET, 0);
    assert(err == -1);

    close(fd);
    return errno;
}
