/* Array of pointers */

#include <stdio.h>
#include <malloc.h>

int main()
{

    char *ptr[10];

    printf("p: %p \n", ptr);
    for (int i = 0; i < 10; i++)
    {
        ptr[i] = (char *)malloc(1);
        *ptr[i] = 10 - i;
        printf("ptr[%d]: %p \n", i, ptr[i]);
    }

    for (int i = 0; i < 10; i++)
    {
        printf(" *ptr[%d]: %d \n", i, *ptr[i]);
    }

    for (int i = 0; i < 10; i++)
    {
        free(ptr[i]);
    }

    // printf("Hello World\n");
    return 0;
}