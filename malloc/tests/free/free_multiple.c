#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Test de : free_multiple.c\n");
    char *a = malloc(1);
    char *b = malloc(4);
    char *c = malloc(42);
    assert(a && b && c);
    free(b);
    free(a);
    free(c);
    printf("Test réussi : free_multiple.c\n");
    return 0;
}
