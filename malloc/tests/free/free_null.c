#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("Test de : free_null.c\n");
    char *res = NULL;
    free(res);
    printf("Test réussi : free_null.c\n");
    return 0;
}
