#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Test de : calloc_small.c\n");
    size_t nmemb = 4;
    size_t size = 8;
    char *res = calloc(nmemb, size);
    assert(res != NULL);
    for (size_t i = 0; i < nmemb * size; i++)
    {
        assert(res[i] == 0);
    }
    free(res);
    printf("Test réussi : calloc_small.c\n");
    return 0;
}
