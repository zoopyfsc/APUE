#include <stdio.h>
#include <wchar.h>

int main()
{
    int res = 0;
    FILE* fp = fopen("test.txt", "a+");
    if (fp == NULL)
    {
        printf("fopen error");
    }

    res = fwide(fp, 0);
    printf("%d", res);
    res = fwide(fp, 1);
    printf("%d", res);
    res = fwide(fp, -1);
    printf("%d", res);
    return 0;

}
