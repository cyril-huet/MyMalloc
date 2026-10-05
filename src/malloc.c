#include "malloc.h"

static struct metadata *g_start = NULL;

static void *init(void)
{
    size_t page_size = sysconf(_SC_PAGESIZE);
    void *res = mmap(NULL, page_size, PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (res == MAP_FAILED)
    {
        return NULL;
    }
    g_start = res;
    g_start->free = 0;
    size_t size_usable = page_size - sizeof(struct metadata);
    g_start->size = size_usable;
    g_start->next = NULL;
    g_start->prev = NULL;
    g_start->page_start = g_start;
    g_start->page_len = page_size;
    return g_start;
}

static struct metadata *find_place(size_t size)
{
    struct metadata *copie = g_start;
    while (copie != NULL)
    {
        if ((copie->free == 0) && copie->size >= size)
        {
            return copie;
        }
        copie = copie->next;
    }
    return NULL;
}

static struct metadata *create_new_size(size_t size)
{
    size_t page_size = sysconf(_SC_PAGESIZE);
    size_t size_metadata = sizeof(struct metadata);
    size_t all_size = page_size;

    while (size + size_metadata > all_size)
    {
        all_size += page_size;
    }
    void *new_size = mmap(NULL, all_size, PROT_READ | PROT_WRITE,
                          MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (new_size == MAP_FAILED)
    {
        return NULL;
    }
    struct metadata *metadata_block = new_size;
    metadata_block->free = 0;
    metadata_block->size = all_size - sizeof(struct metadata);
    metadata_block->next = NULL;
    metadata_block->prev = NULL;
    metadata_block->page_start = metadata_block;
    metadata_block->page_len = all_size;

    if (g_start == NULL)
    {
        g_start = metadata_block;
        return metadata_block;
    }

    struct metadata *copie = g_start;
    while (copie->next != NULL)
    {
        copie = copie->next;
    }
    copie->next = metadata_block;
    metadata_block->prev = copie;
    return metadata_block;
}

static void split(struct metadata *metadata, size_t size)
{
    if (metadata->size <= size + sizeof(struct metadata))
    {
        return;
    }
    struct metadata *to_free;
    struct metadata *keep = metadata;
    to_free = (struct metadata *)((char *)(metadata + 1) + size);
    to_free->free = 0;
    to_free->size = metadata->size - size - sizeof(struct metadata);
    to_free->next = keep->next;
    to_free->prev = keep;
    to_free->page_start = keep->page_start;
    to_free->page_len = keep->page_len;
    keep->free = 1;
    keep->size = size;
    keep->next = to_free;
    if (to_free->next != NULL)
    {
        to_free->next->prev = to_free;
    }
}

static void fusion(struct metadata *prev, struct metadata *next)
{
    if (next == NULL || prev == NULL)
    {
        return;
    }
    if (next->free == 1 || prev->free == 1)
    {
        return;
    }
    if (prev->page_start != next->page_start)
    {
        return;
    }
    size_t new_size = next->size + prev->size + sizeof(struct metadata);
    prev->size = new_size;
    next->size = 0;
    prev->next = next->next;
    if (next->next != NULL)
    {
        next->next->prev = prev;
    }
}

static size_t align(size_t size)
{
    size_t alignment = sizeof(long double);
    size_t remainder = size % alignment;
    size_t extra = 0;

    if (remainder != 0)
    {
        extra = alignment - remainder;
    }

    if (size > SIZE_MAX - extra)
    {
        return 0;
    }

    return size + extra;
}

static int page_empty(struct metadata *page)
{
    struct metadata *page_copie = page;
    while (page_copie != NULL && page_copie->page_start == page->page_start)
    {
        if (page_copie->free == 1)
        {
            return 0;
        }
        page_copie = page_copie->next;
    }
    return 1;
}

__attribute__((visibility("default"))) void *malloc(size_t size)
{
    size_t page_size = sysconf(_SC_PAGESIZE);
    if (size == 0)
    {
        return NULL;
    }
    size = align(size);
    if (size == 0)
    {
        return NULL;
    }
    struct metadata *res = NULL;
    res = find_place(size);
    if (res == NULL)
    {
        if (g_start == NULL)
        {
            size_t size_need = size + sizeof(struct metadata);
            if (size_need > page_size)
            {
                res = create_new_size(size);
            }
            else
            {
                res = init();
            }
        }
        else
        {
            res = create_new_size(size);
        }
    }
    if (res == NULL)
    {
        return NULL;
    }
    split(res, size);
    res->free = 1;
    res++;
    return res;
}

__attribute__((visibility("default"))) void free(void *ptr)
{
    if (ptr == NULL)
    {
        return;
    }
    struct metadata *data = ptr;
    data--;
    if (data->free == 0)
    {
        return;
    }
    data->free = 0;
    if (data->next != NULL && data->next->free == 0
        && data->next->page_start == data->page_start)
    {
        fusion(data, data->next);
    }
    if (data->prev != NULL && data->prev->free == 0
        && data->prev->page_start == data->page_start)
    {
        fusion(data->prev, data);
        data = data->prev;
    }
    if (page_empty(data->page_start) == 1)
    {
        struct metadata *page = data->page_start;
        struct metadata *first_page = page;
        struct metadata *last_page = first_page;
        while (last_page->next
               && last_page->next->page_start == first_page->page_start)
        {
            last_page = last_page->next;
        }
        if (first_page->prev != NULL)
        {
            first_page->prev->next = last_page->next;
        }
        else
        {
            g_start = last_page->next;
        }
        if (last_page->next != NULL)
        {
            last_page->next->prev = first_page->prev;
        }
        munmap(page, page->page_len);
    }
}

__attribute__((visibility("default"))) void *realloc(void *ptr, size_t size)
{
    if (ptr == NULL)
    {
        return malloc(size);
    }
    if (size == 0 && ptr != NULL)
    {
        free(ptr);
        return NULL;
    }
    void *res = malloc(size);
    if (res == NULL)
    {
        return NULL;
    }
    struct metadata *metadata =
        (struct metadata *)((char *)ptr - sizeof(struct metadata));
    size_t past;
    if (size > metadata->size)
    {
        past = metadata->size;
    }
    else
    {
        past = size;
    }
    memcpy(res, ptr, past);
    free(ptr);
    return res;
}

__attribute__((visibility("default"))) void *calloc(size_t nmemb, size_t size)
{
    size_t all_size = 0;
    if (__builtin_mul_overflow(nmemb, size, &all_size) == 1)
    {
        return NULL;
    }
    void *res = malloc(all_size);
    if (res == NULL)
    {
        return NULL;
    }
    memset(res, 0, all_size);
    return res;
}
