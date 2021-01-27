/*
 * APUE exercise 8.1
 */
#include <sys/types.h>
#include <unistd.h>
#include "apue.h"


int globvar = 6;

int main()
{
    int var;
    pid_t   pid;
    var = 88;
    char buf[32];

    printf("befor vfork\n");
    if ((pid = vfork()) < 0)
    {
        err_sys("vfork error");
    }
    else if (pid == 0)
    {
        globvar++;
        var++;
        fclose(stdout);
        _exit(0);
    }

    // parent continues here
    int i = printf("pid = %ld, glob = %d, var = %d\n", (long)getpid(), globvar, var);
    sprintf(buf, "%d\n", i);
    write(STDOUT_FILENO, buf, strlen(buf));
    exit(0);
}
