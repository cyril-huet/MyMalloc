#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Test de : malloc_multiple.c\n");
    char *res1 = malloc(5);
    char *res2 = malloc(42);
    char *res3 = malloc(4096);
    assert(res1 != NULL);
    assert(res2 != NULL);
    assert(res3 != NULL);
    assert(res1 != res2);
    assert(res1 != res3);
    assert(res2 != res3);
    res1[0] = 1;
    res1[4] = 11;
    res2[0] = 2;
    res2[7] = 4;
    res3[0] = 3;
    assert(res1[0] == 1 && res1[4] == 11);
    assert(res2[0] == 2 && res2[7] == 4);
    assert(res3[0] == 3);
    free(res2);
    free(res1);
    free(res3);
    printf("Test réussi : malloc_multiple.c\n");
    return 0;
}
