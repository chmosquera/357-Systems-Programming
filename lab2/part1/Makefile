CC = gcc
CFLAGS = -Wall -ansi -pedantic
MAIN = swap
OBJS = swap.o swap_tests.c
all : $(MAIN)

$(MAIN) : $(OBJS) swap.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

swap.o : swap.c swap.h
	$(CC) $(CFLAGS) -c swap.c

swap_tests.o : swap_tests.c
	$(CC) $(CFLAGS) -c swap_tests.c

clean :
	rm *.o $(MAIN) core
