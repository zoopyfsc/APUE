/*
 * APUE exercise 7.6
 */
#include "apue.h"

int main()
{
    long* lp = calloc(4, sizeof(long));
    int** ap = calloc(4, sizeof(int*));
    for (size_t i = 0; i < 4; i++)
    {
        printf("%u:%ld\n", i, lp[i]);
    }

    for (size_t i = 0; i < 4; i++)
    {
        printf("%u:%p\n", i, ap[i]);
    }
    return 0;
}
