# MyMalloc

A small educational memory allocator written in C.

MyMalloc provides its own implementations of:

- `malloc`
- `free`
- `calloc`
- `realloc`

The goal of the project is to understand how dynamic memory allocation works internally using memory pages, metadata and linked lists.

## Features

- Memory allocation with `mmap`
- First-fit block search
- Block splitting
- Adjacent free block merging
- Support for large allocations
- `malloc`, `free`, `calloc` and `realloc`
- Overflow detection in `calloc`
- Tests for different allocation sizes and behaviours
- Compatible with GCC and Clang on POSIX systems

## How it works

Each allocated memory area contains a small metadata structure before the memory returned to the user.

```text
Allocated page
┌──────────────┬──────────────────────┐
│ Metadata     │ Memory available     │
└──────────────┴──────────────────────┘
```

The allocator keeps the blocks in a linked list. When memory is requested, it:

1. Searches for a free block.
2. Splits the block if it is larger than necessary.
3. Allocates a new page with `mmap` if no block is available.
4. Merges neighbouring free blocks when memory is released.
5. Unmaps a page when all its blocks are free.

## Build

### Requirements

- A C compiler such as GCC or Clang
- GNU Make
- A POSIX-compatible system
- `mmap` and `sysconf`

### Compile

```sh
make
```

This creates:

```text
libmalloc.so
```

### Run the tests

```sh
make check
```

The test suite covers:

- `malloc`
- `calloc`
- `realloc`
- `free`
- Zero-sized allocations
- Multiple allocations
- Large allocations
- Real programs such as `ls`, `cat` and `echo`

### Clean generated files

```sh
make clean
```

## Project structure

```text
.
├── Makefile
├── README.md
├── include/
│   └── malloc.h
├── src/
│   └── malloc.c
└── tests/
    ├── malloc/
    ├── calloc/
    ├── realloc/
    ├── free/
    ├── Makefile
    └── test.sh
```

## Limitations

This allocator is intended for learning and experimentation. It is not a replacement for the system allocator.

Current limitations include:

- No thread synchronization
- No in-place `realloc`
- No advanced allocation strategies
- No Windows support
- No complete validation of invalid pointers
- No benchmark suite

## Learning goals

This project helped me practise:

- Memory management in C
- Pointer arithmetic
- `mmap` and `munmap`
- Linked lists
- Memory alignment
- Overflow detection
- Shared libraries
- Shell-based testing
- Makefiles

## License

See the `LICENSE` file.
