#ifndef MALLOC_H
#define MALLOC_H

#include <assert.h>
#include <err.h>
#include <errno.h>
#include <pthread.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

struct metadata
{
    int free;
    size_t size;
    struct metadata *next;
    struct metadata *prev;
    struct metadata *page_start;
    size_t page_len;
};

void *malloc(size_t size);
void free(void *ptr);
void *realloc(void *ptr, size_t size);
void *calloc(size_t nmemb, size_t size);

#endif /* ! MALLOC_H */
