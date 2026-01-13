CC = gcc
CFLAGS = -Wall -I./utils
TARGET = my_compiler

SRCS = compiler.c utils/custom_io.c utils/file_mgmt.c

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

