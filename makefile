CC = gcc
CFLAGS = -std=c99 -Wall -pedantic

all: graph

clean: 
	rm *.o graph

graph: graph.o lab7.o
	$(CC) $(CFLAGS) lab7.o graph.o -o graph
	
graph.o: graph.c graph.h 
	$(CC) $(CFLAGS) -c graph.c -o graph.o 

lab7.o: lab7.c graph.h
	$(CC) $(CFLAGS) -c lab7.c -o lab7.o 
