CC = gcc
CFLAGS = -Wall -I./utils
TARGET = compiler

SRCS = compiler.c utils/custom_io.c utils/file_mgmt.c utils/lexer_config.c utils/parser.c

all:
	$(CC) $(CFLAGS) $(SRCS) -o $(TARGET)

clean:
	rm -f $(TARGET)

