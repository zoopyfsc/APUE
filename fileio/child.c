#include "apue.h"

int main(int argc, char* argv[])
{
    err_msg("argc = %d\n", argc);

    if (argv[1] == NULL)
    {
        err_msg("There is no Parameter !\n");
        return 0;
    }

    int fd = *argv[1];
    err_msg("child fd = %d\n", fd);

    char *s = "The Child Process Writed !\n";
    ssize_t wb = write(fd, (void *)s, strlen(s));
    if (wb == -1)
    {
        err_msg("The Child Process Write To fd: %d Failed !\n", fd);
    }

    close(fd);
    return 0;
}
