/*
 * APUE exercise 8.7
 */
#include "apue.h"
#include <dirent.h>
#include <fcntl.h>
#include <sys/wait.h>

int main()
{
    DIR *dir;
    int fd;
    int fd_flags;
    char buf[10];
    pid_t   pid;

    if ((dir = opendir("/")) == NULL)
        err_sys("opendir error");

    if ((fd = dirfd(dir)) < 0)
        err_sys("get dir fd error");

    sprintf(buf, "%d", fd);

    if ((fd_flags = fcntl(fd, F_GETFD, 0)) < 0)
        err_sys("get fd flags error");

    if (fd_flags & FD_CLOEXEC)
        printf("close-on-exec is on\n");
    else
        printf("close-on-exec is off\n");

    fd_flags &= ~FD_CLOEXEC;
    fcntl(fd, F_SETFD, fd_flags);


    if ((pid = fork()) < 0)
        err_sys("fork error");
    else if (pid == 0)
    {
        execlp("test8_7_c", "test8_7_c", buf, NULL);
        exit(0);
    }

    if ((pid = waitpid(pid, NULL, 0)) < 0)
        err_sys("waitpid error");

    exit(0);
}
