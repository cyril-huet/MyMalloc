CC = cc
CPPFLAGS = -D_DEFAULT_SOURCE -Iinclude
CFLAGS = -std=c99 -pedantic -Werror -Wall -Wextra -Wvla \
         -fvisibility=hidden -fPIC

LDFLAGS = -shared
OBJS = src/malloc.o
TARGET = libmalloc.so
library: $(TARGET)

$(TARGET): $(OBJS)
		$(CC)  -o $(TARGET) $(OBJS) $(LDFLAGS)

check:
	cd tests && make && ./test.sh
	
clean:
		$(RM) $(OBJS) $(TARGET) $(OBJS)

format:
	clang-format -i src/malloc.c include/malloc.h

check-format:
	clang-format --dry-run -Werror src/malloc.c include/malloc.h

.PHONY: library check format check-format clean
