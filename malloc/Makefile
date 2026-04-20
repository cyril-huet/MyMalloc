CC = gcc
CPPFLAGS = -D_DEFAULT_SOURCE
CFLAGS = -std=c99 -pedantic -Werror -Wall -Wextra -Wvla -fvisibility=hidden -fPIC
LDFLAGS = -shared -Wl,--no-undefined
OBJS = src/malloc.o

TARGET = libmalloc.so

library: $(TARGET)

$(TARGET): $(OBJS)
		$(CC)  -o $(TARGET) $(OBJS) $(LDFLAGS)

check:
	cd tests && make && ./test.sh
	
clean:
		$(RM) $(OBJS) $(TARGET) $(OBJS)

