CC = gcc
CFLAGS = -g -Wall -pedantic
MAIN = ignore
MAIN2 = timeout
OBJS = ignore.o
OBJS2 = timeout.o
all : $(MAIN) $(MAIN2)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

ignore.o : ignore.c
	$(CC) $(CFLAGS) -c ignore.c

timeout.o : timeout.c
	$(CC) $(CFLAGS) -c timeout.c

clean :
	rm *.o $(MAIN) core


