SRCS = $(wildcard /src/*.c)
OBJS = $(SRCS:.c = .o)
CC = gcc
CCFLAGS = -g -Wall -O0

my_app : $(OBJS)
$(CC) $^ -o $@

%.o : %.c
$(CC) -c $< $(CCFLAGS)
clean:
rm *.o
.PHONY:clean