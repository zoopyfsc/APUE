/*
 * APUE exercise 8.3
 */
#include <sys/wait.h>
#include "apue.h"
int main()
{
    pid_t   pid;
    siginfo_t    info;
    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        exit(7);

    if (waitid(P_PID, pid, &info, WEXITED) == -1)
    {
        err_sys("waitid error");
    }
    pr_exit(info.si_status);

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        abort();

    if (waitid(P_PID, pid, &info, WEXITED) == -1)
        err_sys("waitid error");
    pr_exit(info.si_status);

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
    {
        int status = 2;
        status /= 0;
    }

    if (waitid(P_PID, pid, &info, WEXITED) == -1)
        err_sys("waitid error");
    pr_exit(info.si_status);
    return 0;
}
