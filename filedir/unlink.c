#include "apue.h"
#include <fcntl.h>

int main()
{
    // 通常用这种方法确保临时文件不会遗留下来
    if (open("tempfile", O_RDWR) < 0)
        err_sys("open error");
    if (unlink("tempfile") < 0)
        err_sys("unlink error");
    printf("file unlinked\n");

    sleep(15);
    printf("done\n");
    exit(0);
}
