/**
 *
 * dup2() call tests
 *
 **/

#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>

#define FD_MACRO 1000

int main(int argc, char const *argv[])
{
    int oldfd = 1; // stdout
    int newfd = FD_MACRO; // try to dup2 to 1000 fd

    // dup stdout
    newfd = dup2(oldfd, FD_MACRO);
    assert(newfd == -1); // assert error occured

    newfd = dup2(oldfd, FD_MACRO);
    assert(newfd == -1); // assert error occured
    return errno;
}