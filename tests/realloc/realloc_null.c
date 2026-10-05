#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Test de : realloc_null.c\n");
    char *res = realloc(NULL, 100);
    assert(res != NULL);
    res[0] = 42;
    assert(res[0] == 42);
    free(res);
    printf("Test réussi : realloc_null.c\n");
    return 0;
}
