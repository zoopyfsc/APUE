#include "apue.h"

static void sig_usr(int signo)
{
    volatile int i = 0;
    printf("catch sig:%d\n", signo);

    for (; i < 50000000; i++)
    {
    }
    sleep(10);

    printf("catch sig:%d done, i:%d\n", signo, i);
}


int main()
{
    struct sigaction act, oact;
    act.sa_handler = sig_usr;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_flags |= SA_NODEFER;         // 不阻塞此信号
    if (sigaction(SIGQUIT, &act, &oact) < 0)
        err_sys("sigaction error");


    printf("\ntest nodefer\n");
    sleep(50);

    printf("\ntest resethand\n");
    act.sa_handler = sig_usr;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    act.sa_flags |= SA_RESETHAND;       // 重置为SIG_DFL
    if (sigaction(SIGQUIT, &act, &oact) < 0)
        err_sys("sigaction error");

    sleep(50);
    return 0;
}
