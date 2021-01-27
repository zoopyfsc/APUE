/*
 * APUE exercise 8.2
 */
#include <sys/types.h>
#include <unistd.h>

#include "apue.h"

static void f1(), f2();

int main()
{
    f1();
    f2();
    _exit(0);
}

static void f1()
{
    if (vfork() < 0)
        err_sys("vfork error");
}

static void f2()
{
    char buf[1000];
    int i;
    for (i = 0; i < sizeof(buf); i++)
        buf[i] = 0;
}
