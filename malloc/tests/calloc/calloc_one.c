#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Test de : calloc_one.c\n");
    char *res = calloc(1, 1);
    assert(res != NULL);
    assert(res[0] == 0);
    res[0] = 42;
    assert(res[0] == 42);
    free(res);
    printf("Test réussi : calloc_one.c\n");
    return 0;
}
