/*
 * 不可重入实验不成功, 调用alarm只执行了一次 
 */
#include "apue.h"
#include <pwd.h>

static void my_alarm(int signo)
{
    signal(SIGALRM, my_alarm);
    struct passwd *rootptr;

    printf("in signal handler\n");
    if ((rootptr = getpwnam("root")) == NULL)
        err_sys("getpwnam(root) error");
    alarm(1);
}

int main()
{
    struct passwd *ptr;

    signal(SIGALRM, my_alarm);
    alarm(1);

    for (;;)
    {
        if ((ptr = getpwnam("cppuser")) == NULL)
            err_sys("getpwnam error");
        if (strcmp(ptr->pw_name, "cppuser") != 0)
            printf("return value corrupted!, pw_name = %s\n", ptr->pw_name);
//        printf("ptr->pw_name:%s\n", ptr->pw_name);
    }
}
