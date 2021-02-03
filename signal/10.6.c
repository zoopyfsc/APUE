/*
 * APUE exercise 10.6
 */
#include "apue.h"

int main()
{
    pid_t   pid;
    volatile int i = 0;
    TELL_WAIT();
    
    if ((pid = fork()) < 0)
        err_quit("fork error");
    else if (pid == 0)
    {
        while (i < 10)
        {
            WAIT_PARENT();
            ++i;
            printf("i: %d, pid:%d\n", i, getpid());
            TELL_PARENT(getppid());
        }
        _exit(0);
    }

    while (i < 10)
    {
        ++i;
        printf("i: %d, pid:%d\n", i, getpid());
        TELL_CHILD(pid);
        WAIT_CHILD();
    }
    exit(0);
}
