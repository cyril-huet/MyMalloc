#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Test de : realloc_multiple.c\n");
    char *a = malloc(1);
    char *b = malloc(3);
    char *c = malloc(42);
    assert(a && b && c);
    a = realloc(a, 42);
    b = realloc(b, 5);
    c = realloc(c, 9);
    assert(a && b && c);
    free(a);
    free(b);
    free(c);
    printf("Test réussi : realloc_multiple.c\n");
    return 0;
}
