#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Test de : malloc_big.c\n");
    size_t size = 1024 * 4242;
    char *res = malloc(size);
    assert(res != NULL);
    res[0] = 42;
    res[size - 1] = 25;
    assert(res[0] == 42);
    assert(res[size - 1] == 25);
    free(res);
    printf("Test réussi : malloc_big.c\n");
    return 0;
}
