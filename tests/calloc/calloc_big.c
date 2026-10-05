#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Test de : calloc_big.c\n");
    size_t nmemb = 1024;
    size_t size = 4242;
    char *res = calloc(nmemb, size);
    assert(res != NULL);
    for (size_t i = 0; i < nmemb * size; i++)
    {
        assert(res[i] == 0);
    }
    res[0] = 42;
    res[nmemb * size - 1] = 2;
    assert(res[0] == 42);
    assert(res[nmemb * size - 1] == 2);
    free(res);
    printf("Test réussi : calloc_big.c\n");
    return 0;
}
