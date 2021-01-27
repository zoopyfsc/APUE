#include <time.h>
#include <stdio.h>

int main()
{
    time_t tmpcal_ptr;
    struct tm *tmp_ptr = NULL;

    tmpcal_ptr = time(NULL);
    printf("unix timestamp:%ld\n", tmpcal_ptr);

    tmp_ptr = gmtime(&tmpcal_ptr);
    printf("UTC time is: %d:%d:%d\n", tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec);

    tmp_ptr = localtime(&tmpcal_ptr);
    printf("localtime is: %d:%d:%d\n", tmp_ptr->tm_hour, tmp_ptr->tm_min, tmp_ptr->tm_sec);
    return 0;
}
