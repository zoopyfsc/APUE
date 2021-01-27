#include "apue.h"
#include <limits.h>

int main()
{
    char ptr[NAME_MAX];
    if (chdir("/usr") < 0)
        err_sys("chdir failed");
    if (getcwd(ptr, NAME_MAX) == NULL)
        err_sys("getcwd failed");
    printf("cwd = %s\n", ptr);
    exit(0);
}
