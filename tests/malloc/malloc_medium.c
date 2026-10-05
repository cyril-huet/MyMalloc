#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Test de : malloc_medium.c\n");
    size_t size = 42 * 5;
    char *res = malloc(size);
    assert(res != NULL);
    res[0] = 42;
    res[size - 1] = 22;
    assert(res[0] == 42);
    assert(res[size - 1] == 22);
    free(res);
    printf("Test réussi : malloc_medium.c\n");
    return 0;
}
