#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Test de : realloc_small.c\n");
    char *res = malloc(16);
    assert(res != NULL);
    for (int i = 0; i < 16; i++)
    {
        res[i] = i * 4;
    }
    res = realloc(res, 32);
    assert(res != NULL);
    for (int i = 0; i < 16; i++)
    {
        assert(res[i] == i * 4);
    }
    free(res);
    printf("Test réussi : realloc_small.c\n");
    return 0;
}
