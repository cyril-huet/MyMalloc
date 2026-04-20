#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Test de : malloc_null.c\n");
    void *res = malloc(0);
    if (res != NULL)
    {
        free(res);
    }
    printf("Test réussi : malloc_null.c\n");
    return 0;
}
