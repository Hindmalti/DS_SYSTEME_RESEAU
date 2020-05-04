CC = gcc
CFLAGS = -W -Wall
CFLAGS = -Wall -Wextra -pedantic
DFLAGS = -g -DDEBUG

SRC = $(wildcard *.c)
OBJS = $(SRC:.c=.o)
AOUT = mario
 
all : $(AOUT) 
 
mario : $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^
%.o : %.c
	$(CC) $(CFLAGS) -o $@ -c $<
clean :
	@rm *.o
cleaner : clean
	@rm $(AOUT)