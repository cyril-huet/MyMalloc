#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Test de : realloc_medium.c\n");
    size_t old_size = 42;
    size_t new_size = 142;
    char *res = malloc(old_size);
    assert(res != NULL);
    res = realloc(res, new_size);
    assert(res != NULL);
    free(res);
    printf("Test réussi : realloc_medium.c\n");
    return 0;
}
