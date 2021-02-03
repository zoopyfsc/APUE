/*
 * APUE exercise 10.9
 */
#include "apue.h"

void printset(sigset_t *ped)
{
    int i;
    for (i = 1; i < 32; i++)
    {
        if (sigismember(ped, i) == 1)
        {
            printf("%s\n", strsignal(i));
        }
    }
}

int main()
{
    sigset_t    mask, bmask;
    sigemptyset(&mask);
    sigemptyset(&bmask);
    sigaddset(&mask, SIGQUIT);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGUSR1);
    sigaddset(&mask, SIGCHLD);
    sigprocmask(SIG_BLOCK, &mask, NULL);

    sigprocmask(0, NULL, &bmask);
    printset(&bmask);

    exit(0);
}
