/**
 *
 * dup() call tests
 *
 **/

#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <errno.h>

int main(int argc, char const *argv[])
{
    int oldfd = 1; // stdout
    int newfd;

    // dup stdout
    newfd = dup(oldfd);
    assert(newfd == -1); // assert error occured

    newfd = dup(oldfd);
    assert(newfd == -1); // assert error occured
    return errno;
}