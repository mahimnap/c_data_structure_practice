CC = gcc
CFLAGS = -std=c99 -Wall -pedantic

all: test1 test2 test3 test4 test5 test6 test7 test8

clean:
	rm *.o test1 test2 test3 test4 test5 test6 test7 test8

test1: test1.o array.o 
	$(CC) $(CFLAGS) array.o test1.o -o test1
	
test2: test2.o array.o 
	$(CC) $(CFLAGS) array.o test2.o -o test2
	
test3: test3.o array.o 
	$(CC) $(CFLAGS) array.o test3.o -o test3
	
test4: test4.o array.o 
	$(CC) $(CFLAGS) array.o test4.o -o test4
	
test5: test5.o array.o 
	$(CC) $(CFLAGS) array.o test5.o -o test5
	
test6: test6.o array.o 
	$(CC) $(CFLAGS) array.o test6.o -o test6
	
test7: test7.o array.o 
	$(CC) $(CFLAGS) array.o test7.o -o test7
	
test8: test8.o array.o 
	$(CC) $(CFLAGS) array.o test8.o -o test8

array.o: array.c array.h
	$(CC) $(CFLAGS) -c array.c -o array.o

test1.o: test1.c array.h
	$(CC) $(CFLAGS) -c test1.c -o test1.o
	
test2.o: test2.c array.h
	$(CC) $(CFLAGS) -c test2.c -o test2.o
	
test3.o: test3.c array.h
	$(CC) $(CFLAGS) -c test3.c -o test3.o
	
test4.o: test4.c array.h
	$(CC) $(CFLAGS) -c test4.c -o test4.o
	
test5.o: test5.c array.h
	$(CC) $(CFLAGS) -c test5.c -o test5.o

test6.o: test6.c array.h
	$(CC) $(CFLAGS) -c test6.c -o test6.o
	
test7.o: test7.c array.h
	$(CC) $(CFLAGS) -c test7.c -o test7.o
	
test8.o: test8.c array.h
	$(CC) $(CFLAGS) -c test8.c -o test8.o
