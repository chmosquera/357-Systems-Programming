CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
MAIN = my_read
MAIN2 = my_fread
MAIN3 = limits
MAIN4 = shelllimits
OBJS = my_read.o
OBJS2 = my_fread.o
OBJS3 = limits.o
OBJS4 = shelllimits.o

all : $(MAIN) $(MAIN2) $(MAIN3) $(MAIN4)

$(MAIN) : $(OBJS)
	$(CC) $(CFLAGS) -o $(MAIN) $(OBJS)

$(MAIN2) : $(OBJS2)
	$(CC) $(CFLAGS) -o $(MAIN2) $(OBJS2)

$(MAIN3) : $(OBJS3)
	$(CC) $(CFLAGS) -o $(MAIN3) $(OBJS3)

$(MAIN4) : $(OBJS4)
	$(CC) $(CFLAGS) -o $(MAIN4) $(OBJS4)

my_read.o : my_read.c
	$(CC) $(CFLAGS) -c my_read.c

my_fread.o : my_fread.c
	$(CC) $(CFLAGS) -c my_fread.c

limits.o : limits.c
	$(CC) $(CFLAGS) -c limits.c

shelllimits.o : shelllimits.c
	$(CC) $(CFLAGS) -c shelllimits.c

clean :
	rm *.o $(MAIN) core


