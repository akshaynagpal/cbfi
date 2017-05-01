# @author: Kunal Baweja
# 

CC = gcc
TARGET = wraplib.so
CFLAGS=-Wall -shared -fPIC
LDFLAGS=-ldl

# Should be equivalent to your list of C files
SRC=$(wildcard *.c)
# substitute .c with .o
OBJ=$(SRC:.c=.o)

all: $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LDFLAGS)

# compile obj files from all c files
%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

# remove all obj files and TARGET file from current directory
clean:
	$(RM) $(OBJ) $(TARGET)
