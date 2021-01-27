/*
 * APUE exercise 4.13
 */
#include "apue.h"
#include <fcntl.h>
#include <sys/time.h>

int main(int argc, char *argv[])
{
    int i, fd;
    struct stat statbuf;
    struct timeval times[2];

    for (i = 1; i < argc; i++)
    {
        if (stat(argv[i], &statbuf) < 0)
        {
            err_ret("%s: stat error", argv[i]);
            continue;
        }
        if ((fd = open(argv[i], O_RDWR|O_TRUNC)) < 0)
        {
            err_ret("%s: open error", argv[i]);
        }

        // 访问时间
        times[0].tv_sec = statbuf.st_atim.tv_sec;
        times[0].tv_usec = statbuf.st_atim.tv_nsec / 1000;
        times[1].tv_sec = statbuf.st_mtim.tv_sec + 20;
        times[1].tv_usec = statbuf.st_mtim.tv_nsec / 1000 + 100;
        if (utimes(argv[i], times) < 0)
        {
            err_ret("%s: utimes error", argv[i]);
        }
        close(fd);
    }
    exit(0);
}
