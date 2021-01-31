#include <errno.h>
#include "apue.h"

void pr_mask(const char* str)
{
    sigset_t    sigset;
    int     errno_save;

    errno_save = errno;
    // sigprocmask是仅为单线程进程定义的
    // 获取当前设置阻塞的信号集
    if (sigprocmask(0, NULL, &sigset) < 0)
    {
        err_ret("sigprocmask error");
    }
    else
    {
        printf("%s", str);
        if (sigismember(&sigset, SIGINT))
            printf(" SIGINT");
        if (sigismember(&sigset, SIGQUIT))
            printf(" SIGQUIT");
        if (sigismember(&sigset, SIGUSR1))
            printf(" SIGUSR1");
        if (sigismember(&sigset, SIGALRM))
            printf(" SIGALRM");

        printf("\n");
    } 

    errno = errno_save;
}

int main()
{
    pr_mask("mask");
    exit(0);
}
