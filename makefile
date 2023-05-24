CC = gcc
CFLAGS = -std=c99 -Wall -pedantic

all: ttest

clean: 
	rm *.o ttest
	
ttest: ttest.o tree.o
	$(CC) $(CFLAGS) ttest.o tree.o -o ttest 
	
tree.o: tree.c tree.h
	$(CC) $(CFLAGS) -c tree.c -o tree.o
	
ttest.o: ttest.c tree.h
	$(CC) $(CFLAGS) -c ttest.c -o ttest.o 
