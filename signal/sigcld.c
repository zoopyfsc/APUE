/*
 * ubuntu16.04 测试未生效
 */
#include "apue.h"
#include <sys/wait.h>

static void sig_cld(int);

int main()
{
    pid_t   pid;

    // 设成成SIG_IGN会不产生僵尸进程
    if (signal(SIGCHLD, sig_cld) == SIG_ERR)
        perror("signal error");
    
    if ((pid = fork()) < 0)
    {
        perror("fork error");
    }
    else if (pid == 0)
    {
        sleep(2);
        _exit(0);
    }

    pause();
    exit(0);
}

static void sig_cld(int signo)
{
    pid_t   pid;
    int status;

    printf("SIGCHLD received\n");

    // 会立即检查是否有子进程准备好被等待，如果有立即调用处理程序
//    if (signal(SIGCHLD, sig_cld) == SIG_ERR)
//        perror("signal error");

    if ((pid = wait(&status)) < 0)
        perror("wait error");

    printf("pid = %d\n", pid);
}
