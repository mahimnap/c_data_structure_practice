CC = gcc
CFLAGS = -std=c99 -pedantic -Wall

all: test_getbytes test_getbits test_bits2ll test_bits2ull test_spff test_dpff print_preface

clean: 
	-rm *.o test_getbytes test_getbits test_bits2ll test_bits2ull test_spff test_dpff
	
print_preface:
	@echo "DPFF AND SPFF ARE NOT IMPLEMENTED YET!"
	@echo "Tab indentation used (1 - 8 spc), and most comments are withihn header"
	@echo "./test_case_of_your_choosing"

test_getbytes: bandb.o test_getbytes.o
	$(CC) $(CFLAGS) bandb.o test_getbytes.o -o test_getbytes
	
test_getbits: bandb.o test_getbits.o
	$(CC) $(CFLAGS) bandb.o test_getbits.o -o test_getbits
	
test_bits2ull: bandb.o test_bits2ull.o
	$(CC) $(CFLAGS) bandb.o test_bits2ull.o -o test_bits2ull 

test_bits2ll: bandb.o test_bits2ll.o
	$(CC) $(CFLAGS) bandb.o test_bits2ll.o -o test_bits2ll

test_spff: bandb.o test_spff.o
	$(CC) $(CFLAGS) bandb.o test_spff.o -o test_spff
	
test_dpff: bandb.o test_dpff.o
	$(CC) $(CFLAGS) bandb.o test_dpff.o -o test_dpff
	
bandb.o: bandb.c 
	$(CC) $(CFLAGS) -c bandb.c -o bandb.o

test_getbytes.o: test_getbytes.c
	$(CC) $(CFLAGS) -c test_getbytes.c -o test_getbytes.o
	
test_getbits.o: test_getbits.c
	$(CC) $(CFLAGS) -c test_getbits.c -o test_getbits.o
	
test_bits2ull.o: test_bits2ull.c
	$(CC) $(CFLAGS) -c test_bits2ull.c -o test_bits2ull.o
	
test_bits2ll.o: test_bits2ll.c
	$(CC) $(CFLAGS) -c test_bits2ll.c -o test_bits2ll.o

test_spff.o: test_spff.c
	$(CC) $(CFLAGS) -c test_spff.c -o test_spff.o
	
test_dpff.o: test_dpff.c
	$(CC) $(CFLAGS) -c test_dpff.c -o test_dpff.o
