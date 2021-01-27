
#include <sys/wait.h>
#include "apue.h"

int main()
{
    pid_t pid;
    int status;

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)
    {
        exit(7);
    }

    // wait for child
    if (wait(&status) != pid)
    {
        err_sys("wait error");
    }

    pr_exit(status);

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)
    {
        // generates SIGABRT
        abort();
    }

    if (wait(&status) != pid)
    {
        err_sys("wait error");
    }
    pr_exit(status);

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)
    {
        // generates SIGFPE
        status /= 0;
    }

    if (wait(&status) != pid)
    {
        err_sys("wait error");
    }
    pr_exit(status);

    exit(0);
}
