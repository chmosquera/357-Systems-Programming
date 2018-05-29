CC = gcc
CFLAGS = -Wall -ansi -pedantic
MAIN = part4
OBJS = part4.o part4_tests.o
all : $(MAIN)

$(MAIN) : $(OBJS) part4.h
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

part4.o : part4.c part4.h
	$(CC) $(CFLAGS) -c part4.c

part4_tests.o : part4_tests.c
	$(CC) $(CFLAGS) -c part4_tests.c

clean :
	rm *.o $(MAIN) core

