#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Test de : free_after_free_read.c\n");
    char *res1 = malloc(42);
    assert(res1 != NULL);
    res1[0] = 42;
    free(res1);
    char *res2 = malloc(42);
    assert(res2 != NULL);
    res2[0] = 43;
    assert(res2[0] == 43);
    free(res2);
    printf("Test réussi : free_after_free_read.c\n");
    return 0;
}
