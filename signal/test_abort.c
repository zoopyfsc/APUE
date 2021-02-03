#include "apue.h"

int main()
{
    // abort不理会进程对SIGABRT的阻塞和忽略
    sigset_t    mask; 
    sigemptyset(&mask);
    sigaddset(&mask, SIGABRT);
    if (sigprocmask(SIG_BLOCK, &mask, NULL) < 0)
        err_sys("SIG_BLOCK error");

    printf("block abort\n");
    abort(); 
    printf("done\n");
    exit(0);
}
