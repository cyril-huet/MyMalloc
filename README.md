# Malloc

Malloc is a custom implementation of the standard memory allocation functions
provided by the C standard library. The goal of this project is to understand
how dynamic memory management works internally, by building a shared library
that overrides libc's allocator.

This implementation provides its own versions of:
- malloc
- free
- calloc
- realloc

The allocator directly interacts with the operating system using low-level
system calls such as `mmap`, `munmap`, and `mremap`.

---

## Overview

This project focuses on low-level system programming concepts such as:
- memory management
- virtual memory mapping
- pointer arithmetic
- fragmentation handling
- performance optimization
- thread safety (advanced)

The allocator must respect the behavior defined in the manual pages
(`man malloc`, `man free`, etc.).

---

## Features

### Core features

- `malloc(size_t size)`
  - Allocates a memory block aligned on `long double`
  - Returns NULL on failure

- `free(void *ptr)`
  - Frees allocated memory
  - Does nothing if `ptr == NULL`

- `calloc(size_t nmemb, size_t size)`
  - Allocates and zero-initializes memory
  - Handles overflow

- `realloc(void *ptr, size_t size)`
  - Resizes a memory block
  - May move memory if needed

---

### Advanced features (optional)

- Thread-safe allocator (mutex / locking)
- Optimized `realloc`
- Reduced fragmentation
- Corruption-resistant metadata
- Improved memory footprint
- Real-world usage compatibility

---

## Constraints

- Only allowed system calls:
  - `mmap`
  - `munmap`
  - `mremap`
  - `sysconf`

- Allowed headers:
  - string.h
  - sys/mman.h
  - pthread.h
  - stdint.h
  - err.h
  - errno.h
  - assert.h
  - stddef.h
## Build
Build the shared library using:

```sh
make
```
### This will produce:
```sh
libmalloc.so
```
## Usage
### Link manually
```sh
gcc main.c -L. -lmalloc -o main
LD_LIBRARY_PATH=. ./main
```
### Use with preload
```sh
LD_PRELOAD=./libmalloc.so ls
```


