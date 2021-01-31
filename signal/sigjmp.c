#include <errno.h>
#include "apue.h"
#include <setjmp.h>
#include <time.h>

static void sig_usr1(int);
static void sig_alrm(int);
static sigjmp_buf   jmpbuf;
static volatile sig_atomic_t    canjump;    // 写这种类型的变量时不会被中断


Sigfunc* signal1(int signo, Sigfunc* func)
{
    struct sigaction act, oact;
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if (signo == SIGALRM)
    {
#ifdef SA_INTERRUPT 
        // 定义SA_INTERRUPT标志,则系统调用被中断后不再重新启动
        act.sa_flags |= SA_INTERRUPT; 
#endif
    }
    else
    {
        // 显示指定SA_RESTART, 否则sigaction函数不再重启动被中断的系统调用
        act.sa_flags |= SA_RESTART;
    }

    if (sigaction(signo, &act, &oact) < 0)
    {
        return SIG_ERR;
    }
    return oact.sa_handler;
}

void pr_mask(const char *str)
{
    sigset_t    sigset;
    int         errno_save;

    errno_save = errno;
    if (sigprocmask(0, NULL, &sigset) < 0)
        err_ret("sigprocmask error");
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
    if (signal1(SIGUSR1, sig_usr1) == SIG_ERR)
        err_sys("signal(SIGUSR1) error");

    if (signal1(SIGALRM, sig_alrm) == SIG_ERR)
        err_sys("signal(SIGALRM) error");

    pr_mask("start main: ");

    if (sigsetjmp(jmpbuf, 1))

    {
        pr_mask("ending main: ");
        exit(0);
    }

    canjump = 1;
    for (;;)
        pause();

}

static void sig_usr1(int signo)
{
    time_t  starttime;

    if (canjump == 0)
        return;

    pr_mask("starting sig_usr1: ");

    alarm(3);
    starttime = time(NULL);
    for (;;)
        if (time(NULL) > starttime + 5)
            break;

    pr_mask("finishing sig_usr1: ");

    canjump = 0;
    siglongjmp(jmpbuf, 1);
}

static void sig_alrm(int signo)
{
    pr_mask("in sig_alrm: ");
}
