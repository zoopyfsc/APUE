#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include "apue.h"

static volatile sig_atomic_t sigflag;
static sigset_t newmask, oldmask, zeromask;

Sigfunc* apue_signal(int signo, Sigfunc* func)
{
    struct sigaction act, oact;
    act.sa_handler = func;
    sigemptyset(&act.sa_mask);
    act.sa_flags = 0;
    if (signo == SIGALRM)
    {
#ifdef SA_INTERRUPT
        act.sa_flags |= SA_INTERRUPT;
#endif 
    }
    else
    {
        act.sa_flags |= SA_RESTART;
    }

    if (sigaction(signo, &act, &oact) < 0)
        return SIG_ERR;
    return oact.sa_handler;
}

void pr_mask(const char* str)
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
    }
    printf("\n");
    errno = errno_save;
}

static void sig_usr(int signo)
{
    sigflag = 1;
}

void TELL_WAIT(void)
{
    if (apue_signal(SIGUSR1, sig_usr) == SIG_ERR)
        err_sys("signal(SIGUSR1) error");
    if (apue_signal(SIGUSR2, sig_usr) == SIG_ERR)
        err_sys("signal(SIGUSR2) error");
    sigemptyset(&zeromask);
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGUSR1);
    sigaddset(&newmask, SIGUSR2);

    // Block SIGUSR1 and SIGUSR2 and save current signal mask
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        err_sys("SIG_BLOCK error");
}

void TELL_PARENT(pid_t pid)
{
    kill(pid, SIGUSR2);
}

void WAIT_PARENT()
{
    while (sigflag == 0)
        sigsuspend(&zeromask);      // wait for parent

    sigflag = 0;

    // Reset signal mask to original value
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        err_sys("SIG_SETMASK error");
}


void TELL_CHILD(pid_t pid)
{
    kill(pid, SIGUSR1); 
}

void WAIT_CHILD()
{
    while (sigflag == 0)
        sigsuspend(&zeromask);

    sigflag = 0;

    // Reset
    if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
        err_sys("SIG_SETMASK error");
}

void apue_abort()
{
    sigset_t    mask;
    struct sigaction action;

    // Caller can't ignore SIGABRT, if so reset to default
    sigaction(SIGABRT, NULL, &action);
    if (action.sa_handler == SIG_IGN)
    {
        action.sa_handler = SIG_DFL;
        sigaction(SIGABRT, &action, NULL);
    }
    if (action.sa_handler == SIG_DFL)
        fflush(NULL);       // flush all open stdio streams

    // Caller can't block SIGABRT, make surt it's unblocked
    sigfillset(&mask);
    sigdelset(&mask, SIGABRT);
    sigprocmask(SIG_SETMASK, &mask, NULL);

    kill(getpid(), SIGABRT);

    // If we're here, process caught SIGABRT and returned
    fflush(NULL);
    action.sa_handler = SIG_DFL;
    // reset to default
    sigaction(SIGABRT, &action, NULL);
    sigprocmask(SIG_SETMASK, &mask, NULL);
    kill(getpid(), SIGABRT);
    exit(1);
}

// 忽略SIGINT和SIGQUIT信号,并阻塞SIGCHLD信号
int apue_system(const char* cmdstring)
{
    pid_t   pid;
    int     status;
    struct  sigaction   ignore, saveintr, savequit;
    sigset_t    chldmask, savemask;

    if (cmdstring == NULL)
        return 1;

    ignore.sa_handler = SIG_IGN;
    sigemptyset(&ignore.sa_mask);
    ignore.sa_flags = 0;
    if (sigaction(SIGINT, &ignore, &saveintr) < 0)
        return -1;
    if (sigaction(SIGQUIT, &ignore, &savequit) < 0)
        return -1;

    // block SIGCHLD
    sigemptyset(&chldmask);
    sigaddset(&chldmask, SIGCHLD);
    if (sigprocmask(SIG_BLOCK, &chldmask, &savemask) < 0)
        return -1;

    if ((pid = fork()) < 0)
    {
        status = -1;
    }
    else if (pid == 0)
    {
        // restore previous signal actions & reset signal mask
        sigaction(SIGINT, &saveintr, NULL);
        sigaction(SIGQUIT, &savequit, NULL);
        sigprocmask(SIG_SETMASK, &savemask, NULL);

        execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
        _exit(127);
    }
    else
    {
        while (waitpid(pid, &status, 0) < 0)
        {
            if (errno != EINTR)
            {
                status = -1;
                break;
            }
        }
    }

    // restore previous signal actions & reset signal mask
    if (sigaction(SIGINT, &saveintr, NULL))
        return -1;
    if (sigaction(SIGQUIT, &savequit, NULL))
        return -1;
    if (sigprocmask(SIG_SETMASK, &savemask, NULL) < 0)
        return -1;

    return status;
}


static void sig_alrm()
{
}

unsigned int sleep(unsigned int seconds)
{
    struct sigaction newact, oldact;
    sigset_t    newmask, oldmask, suspmask;
    unsigned int unslept;

    newact.sa_handler = sig_alrm;
    sigemptyset(&newact.sa_mask);
    newact.sa_flags = 0;
    sigaction(SIGALRM, &newact, &oldact);

    // block SIGALRM and save current signal mask
    sigemptyset(&newmask);
    sigaddset(&newmask, SIGALRM);
    sigprocmask(SIG_BLOCK, &newmask, &oldmask);

    alarm(seconds);
    suspmask = oldmask;

    sigdelset(&suspmask, SIGALRM);
    // make sure SIGALRM isn't blocked
    sigsuspend(&suspmask);

    // some signal has been caught, SIGALRM is now blocked
    unslept = alarm(0);

    // reset previous action
    sigaction(SIGALRM, &oldact, NULL);

    // reset signal mask
    sigprocmask(SIG_SETMASK, &oldmask, NULL);
    return unslept;
}
