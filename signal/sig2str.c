/*
 * APUE exercise 10.2:q
 */
#include "apue.h"

int sig2str(int signo, char *str)
{
    char* msg = strsignal(signo);
    if (msg == NULL)
        return -1;
    memcpy(str, msg, strlen(msg) + 1);
    return 0;
}

int main()
{
    char str[1024];
    sig2str(SIGQUIT, str);
    printf("%s\n", str);
    exit(0);
}
