/**
 *
 * Test execl
 *
 **/

#include <unistd.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    int ret, pid;
    pid = fork();
    char *envp[] = { NULL };
    char *args[] = { "/bin/ls", NULL };

    // child process
    if (pid == 0) {
        ret = execve("/bin/ls", args, envp);
        assert(ret!=-1);
    }
    else
        waitpid(pid, NULL, 0);

    return 0;
}