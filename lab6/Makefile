CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
MAIN = mystat
OBJS = mystat.o
all : $(MAIN)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

stat.o : mystat.c
	$(CC) $(CFLAGS) -c mystat.c mystat.h

clean :
	rm *.o $(MAIN) core


