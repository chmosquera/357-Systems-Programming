CC = gcc
CFLAGS = -Wall -ansi -pedantic -std=c99
MAIN = square_plus1 
MAIN2 = pipeit
OBJS = square_plus1.o
OBJS2 = pipeit.o
all : $(MAIN) $(MAIN2)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

$(MAIN2) : $(OBJS2)
	$(CC) $(CFLAGS) -o $(MAIN2) $(OBJS2)

square_plus1.o : square_plus1.c
	$(CC) $(CFLAGS) -c square_plus1.c

pipeit.o : pipeit.c
	$(CC) $(CFLAGS) -c pipeit.c

clean : 
	rm *.o $(MAIN) core
