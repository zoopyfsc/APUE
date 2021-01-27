#include "apue.h"
#include <fcntl.h>
#include <sys/wait.h>
int main()
{
    int fd = open("test.txt", O_RDWR|O_APPEND|O_CREAT|O_CLOEXEC, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

    if (fd == -1)
    {
        err_msg("The file test.txt open failed ! The fd = %d\n", fd);
        return 0;
    }
    err_msg("fork!\n");
    int fd1 = dup(fd);

    char *s = "The Parent Process Wirted !\n";
    pid_t pid = fork();
    if (pid == 0)
    {
        err_msg("****** exec child ******\n");
        execl("child", "./child", &fd1, NULL);
        err_msg("************************\n");
    }

    wait(NULL);
    ssize_t wb = write(fd, s, strlen(s));
    if (wb == -1)
    {
        err_msg("The Parent Process Write To fd: %d Failed!\n", fd);
    }
    close(fd);
    close(fd1);
    return 0;
}
