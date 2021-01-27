/*
 * APUE exercise 3.3
 */
#include "apue.h"
#include <fcntl.h>

void fileflag(int fd)
{
    int val;
    if ((val = fcntl(fd, F_GETFL, 0)) < 0)
    {
        err_sys("fcntl error for fd %d", fd);
    }
    printf("fd %d: ", fd);
    switch(val & O_ACCMODE)
    {
        case O_RDONLY:
            printf("read only");
            break;
        case O_WRONLY:
            printf("write only");
            break;
        case O_RDWR:
            printf("read write");
            break;
        default:
            err_dump("unknow access mode");
    }

    if (val & O_APPEND)
    {
        printf(", append");
    }
    if (val & O_NONBLOCK)
    {
        printf(", nonblocking");
    }
    if (val & O_SYNC)
    {
        printf(", synchronous writes");
    }
    printf("\n");
}

int main()
{
    int fd1, fd2, fd3;

    fd1 = open("test.txt", O_RDWR | O_CREAT | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
    if (fd1 < 0)
    {
        err_quit("open failed fd1");
    }
    fd2 = dup(fd1);
    fd3 = open("test.txt", O_RDWR | O_APPEND);
    if (fd3 < 0)
    {
        perror("fd3:");
        err_quit("open failed fd3");
    }
    fileflag(fd1);
    fileflag(fd2);
    fileflag(fd3);

    int flag;
    if ((flag = fcntl(fd1, F_GETFL, 0)) < 0)
    {
        err_quit("fcntl error for fd1.");
    }
    flag |= O_NONBLOCK;
    fcntl(fd1, F_SETFL, flag);
    fileflag(fd1);
    fileflag(fd2);
    fileflag(fd3);

    close(fd1);
    close(fd2);
    close(fd3);
    exit(0);
}
