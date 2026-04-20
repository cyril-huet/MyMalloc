#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Test de : calloc_multiple.c\n");
    char *res1 = calloc(42, 4);
    char *res2 = calloc(4242, 1);
    char *res3 = calloc(2, 4);
    assert(res1 != NULL);
    assert(res2 != NULL);
    assert(res3 != NULL);
    assert(res1 != res2);
    assert(res1 != res3);
    assert(res2 != res3);
    free(res2);
    free(res1);
    free(res3);
    printf("Test réussi : calloc_multiple.c\n");
    return 0;
}
