# @author: Kunal Baweja
# 

CC = gcc
CFLAGS=-Wall --coverage

# Should be equivalent to your list of C files
SRC=$(wildcard *.c)
# substitute .c with .o
TARGET=$(SRC:.c=)
GCNO=$(SRC:.c=.gcno)
GCDA=$(SRC:.c=.gcda)

all: $(TARGET)

%: %.c
	$(CC) $(CFLAGS) -o $@ $<

# remove all obj files and TARGET file from current directory
clean:
	$(RM) $(TARGET) $(GCNO) $(GCDA)
