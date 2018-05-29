CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
MAIN = smake
OBJS = smake.o functions.o linkedlist.o
all : $(MAIN)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

smake.o : smake.c
	$(CC) $(CFLAGS) -c smake.c

functions.o : functions.c functions.h
	$(CC) $(CFLAGS) -c functions.c

linkedlist.o : linkedlist.c linkedlist.h
	$(CC) $(CFLAGS) -c linkedlist.c

clean :
	rm *.o $(MAIN) core


