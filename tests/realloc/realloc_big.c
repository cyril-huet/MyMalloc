#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Test de : realloc_big.c\n");
    size_t old_size = 1024;
    size_t new_size = 424242;
    char *res = malloc(old_size);
    assert(res != NULL);
    res[0] = 1;
    res = realloc(res, new_size);
    assert(res != NULL);
    assert(res[0] == 1);
    free(res);
    printf("Test réussi : realloc_big.c\n");
    return 0;
}
