#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Test de : calloc_null.c\n");
    char *res1 = calloc(0, 42);
    if (res1 != NULL)
    {
        free(res1);
    }
    char *res2 = calloc(42, 0);
    if (res2 != NULL)
    {
        free(res2);
    }
    char *res3 = calloc(0, 0);
    if (res3 != NULL)
    {
        free(res3);
    }
    printf("Test réussi : calloc_null.c\n");
    return 0;
}
