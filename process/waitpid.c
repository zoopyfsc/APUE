/*fork一个子进程,不要它等待子进程终止,也不希望子进程处理僵死状态直到进程终止*/
#include <sys/types.h>
#include <sys/wait.h>

#include "apue.h"

int main()
{
    pid_t pid;

    if ((pid = fork()) < 0)
    {
        err_sys("fork error");
    }
    else if (pid == 0)
    {
        // 第一个子进程创建第二个子进程
        if ((pid = fork()) < 0)
        {
            err_sys("fork error");
        }
        else if (pid > 0)
        {
            // 结束第二个子进程的父进程,也就是第一个子进程
            exit(0);
        }

        sleep(2);
        printf("second child, parent pid = %ld\n", (long)getppid());
        exit(0);
    }

    if (waitpid(pid, NULL, 0) != pid)
    {
        err_sys("waitpid error");
    }

    exit(0);
}
