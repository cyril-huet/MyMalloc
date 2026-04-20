CC = gcc
CFLAGS = -std=c99 -pedantic -Werror -Wall -Wextra -Wvla

MALLOC_TESTS = malloc/malloc_one malloc/malloc_small malloc/malloc_medium malloc/malloc_big malloc/malloc_multiple malloc/malloc_zero
CALLOC_TESTS = calloc/calloc_one calloc/calloc_small calloc/calloc_medium calloc/calloc_big calloc/calloc_multiple calloc/calloc_null calloc/calloc_zero
REALLOC_TESTS = realloc/realloc_one realloc/realloc_small realloc/realloc_medium realloc/realloc_big realloc/realloc_multiple realloc/realloc_null
FREE_TESTS = free/free_one free/free_multiple free/free_null free/free_after

TESTS = $(MALLOC_TESTS) $(CALLOC_TESTS) $(REALLOC_TESTS) $(FREE_TESTS)

all: $(TESTS)

$(MALLOC_TESTS):
	$(CC) $(CFLAGS) -L.. -lmalloc $@.c -o $@

$(CALLOC_TESTS):
	$(CC) $(CFLAGS) -L.. -lmalloc $@.c -o $@

$(REALLOC_TESTS):
	$(CC) $(CFLAGS) -L.. -lmalloc $@.c -o $@

$(FREE_TESTS):
	$(CC) $(CFLAGS) -L.. -lmalloc $@.c -o $@

clean:
	rm -f $(TESTS)

