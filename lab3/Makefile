CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
MAIN = test
OBJS = readline.o test.o
all : $(MAIN)

$(MAIN) : $(OBJS) readline.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

readline.o : readline.c readline.h
	$(CC) $(CFLAGS) -c readline.c

tests.o : test.c
	$(CC) $(CFLAGS) -c test.c

clean :
	rm *.o $(MAIN) core
