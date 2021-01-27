/*
 * APUE exercise 8.6
 */
#include "apue.h"

int main()
{
    pid_t   pid;

    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
        _exit(0);

    sleep(4);
    system("ps aux | grep system");
    exit(0);
}
