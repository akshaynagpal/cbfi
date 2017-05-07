/**
 *
 * Test execl
 *
 **/

#include <unistd.h>
#include <assert.h>
#include <errno.h>

int main(int argc, char const *argv[]) {
    int pid;

    pid = fork();
    assert(pid==-1); // assert fork failure

    pid = fork();
    assert(pid==-1); // assert fork failure
    return errno;
}