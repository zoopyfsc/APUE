/*
 * APUE exercise 4.16
 */
#include "apue.h"
#include <fcntl.h>
#include <limits.h>

int main()
{
    char path[819200];
    char *dir = "TT";
    char *name = "abcdefghijklmnopqrstuvwxyz";
    int i = 0;
    char *buf;
    for (; i < NAME_MAX; i++)
    {
        if (mkdir(dir, DIR_MODE) < 0)
        {
            err_sys("mkdir failed, i =  %d", i);
        }
        if (chdir(dir) < 0)
        {
            err_sys("chdir failed, i = %d", i);
        }
    }

    if (creat(name, FILE_MODE) < 0)
    {
        err_sys("creat error");
    }
    buf = getcwd(path, 81920);
    if (buf == NULL)
    {
        perror("getcwd failed:");
    }
    printf("%s\n", path);
    printf("%s\n", buf);
    exit(0);
}
