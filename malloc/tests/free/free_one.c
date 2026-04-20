#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Test de : free_one.c\n");
    char *res = malloc(1);
    assert(res != NULL);
    res[0] = 42;
    free(res);
    printf("Test réussi : free_one.c\n");
    return 0;
}
