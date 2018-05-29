CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
MAIN = f_test
MAIN2 = odds
MAIN3 = evens
MAIN4 = fe_test
MAIN5 = to_file
all : $(MAIN) $(MAIN2) $(MAIN3) $(MAIN4) $(MAIN5)

$(MAIN) : f_test.c
	$(CC) $(CFLAGS) -o $(MAIN) f_test.c

$(MAIN2) : odds.c
	$(CC) $(CFLAGS) -o $(MAIN2) odds.c

$(MAIN3) : evens.c
	$(CC) $(CFLAGS) -o $(MAIN3) evens.c

$(MAIN4) : fe_test.c
	$(CC) $(CFLAGS) -o $(MAIN4) fe_test.c

$(MAIN5) : to_file.c
	$(CC) $(CFLAGS) -o $(MAIN5) to_file.c

clean :
	rm *.o $(MAIN) core



