/**
 *
 * Test execl
 *
 **/

#include <unistd.h>
#include <signal.h>
#include <assert.h>
#include <stdio.h>
#include <errno.h>
#include <wait.h>
#include "cbfi.h"

int main(int argc, char const *argv[]) {
    int pid, err;

    pid = fork();

    // ask parent to terminate child
    if (pid > 0)
    {
        err = kill(pid, SIGKILL);
        assert(err == -1);

        err = kill(pid, SIGKILL);
        assert(err == -1);

        wait (NULL);
    }
    else if (pid == 0) {
        printf("kill fail should prevent child sleep\n");
        sleep(5);  // sleep 5 seconds
    }
    return errno;
}