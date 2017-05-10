#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <assert.h>
#include "cbfi.h"

int main(){
    int fd, err;
    char *str = "sample-string";
    size_t len = strlen(str) * sizeof(char);

    fd = open("opentest1.txt", O_RDWR);
    assert(fd != -1);

    err = write(fd, str, len);
    assert(err == -1);	// write fail

    err = write(fd, str, len);
    assert(err == -1);  // write fail

    close(fd);
    return errno;
}
