/*
 * APUE exercise 3.6
 */
#include "apue.h"
#include <fcntl.h>

int main()
{
    int fd;
    if ((fd = open("test.txt", O_RDWR | O_APPEND, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)) < 0)
    {
        err_sys("open fd error");
    }

    char *s1 = "hello";
    ssize_t wb = write(fd, (void *)s1, strlen(s1));
    if (wb < 0)
    {
        err_sys("write error");
    }
    printf("write s1 success\n");

    if (lseek(fd, 0, SEEK_SET) == -1)
    {
        err_sys("seek failed");
    }
    
    char buf[5];
    ssize_t rb = read(fd, (void *)buf, 5);
    if (rb < 0)
    {
        err_sys("read error");
    }
    printf("%s\n", buf);

    wb = write(fd, (void*)buf, 5);
    if (wb < 0)
    {
        err_sys("write error");
    }
    printf("write buf success\n");
    return 0;
}
