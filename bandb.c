/*
 * CIS 2520 (0101) Assignment 1
 * Mahimna Pyakuryal
 * 1014826
 * mpyakury
 * 
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <math.h>
#include <string.h>
#include "bandb.h"
#define MAX_STRLEN 64 
//max data type is long long = 8 bytes x 8 bits = 64 chars required to represent each char as a binary '0' or '1'

void getbytes(unsigned char dest[], int bytes, void *src, int reverse){
	int i = 0;
	unsigned char *revAddHold = src;
	revAddHold = (unsigned char*)revAddHold + (bytes - 1); 
	//will be used to decrement if int reverse is set
	
	if (reverse == 0){
		memcpy (dest, src, bytes); 
		//copy all at once if regular order
		src = &dest;
	}
	else if (reverse == 1){
		for (i = 0; i < bytes; i++){
			dest[i] = revAddHold[0]; 
			//copy data at end of source pointed to by revAddHold and add it to dest 1 byte at a time
			revAddHold = (unsigned char*) revAddHold - 1;
		}
	}
}

void getbits(char dest[], int bytes, void *src, int start, int end){
	unsigned short numValSrc = *(unsigned short int*)src;
	unsigned short temp;
	int remainder; 
	int shift; 
	int quotient;
	int i;
	int stringCnt = 0;

	for (i = start; i > end; i--){
		quotient = i / 8; 
		remainder = i % 8; 
		shift = remainder + (quotient * 8); //determine how much is needed to shift to end through remainder and quotient 
		temp = numValSrc>>shift;
		if ((temp&1) == 1){ 
			// anything &1 is either 1 or 0 (depending on is LSB is set). store char representation of binary in destination 
			dest[stringCnt] = '1'; 
			stringCnt++;
		}
		else{
			dest[stringCnt] = '0'; 
			stringCnt++;
		}	
	}
	
	dest[stringCnt] = '\0'; //NULL terminated	
}

unsigned long long bits2ull (char *bits){
	int strLen = strlen (bits) - 1;
	char stringHolder[MAX_STRLEN];
	unsigned long long valHolder = 0;
	int i = 0; 
	int j = 0;
	
	for (i = strLen; i >= 0; i--){ 
		stringHolder[j] = bits[i]; //storing the bits backwards in order of magnitude needed for math just ease (2^0, 2^1, 2^3  etc.)
		j++;
	}
	
	stringHolder[strLen + 1] = '\0';
	
	for (i = 0;  i < strlen (stringHolder); i++){ 
		if (stringHolder[i] == '1'){
			valHolder = valHolder + myPow(i); //call myPow function that returns the (2^i)
		}
	}
	
	return valHolder;
	
}


long long bits2ll (char *bits){ 
	int strLen = strlen (bits) - 1; 
	char stringHolder[MAX_STRLEN];
	unsigned long long valHolder = 0;
	int i = 0; 
	int j = 0;
	
	for (i = strLen; i >= 0; i--){ 
		stringHolder[j] = bits[i];
		j++;
	}
	
	stringHolder[strLen + 1] = '\0';
	
	for (i = 0;  i < strlen (stringHolder); i++){
		if (stringHolder[i] == '1'){
			valHolder = valHolder + myPow(i);
		}
	}
	
	valHolder = ~valHolder; //gets 1s complement of value (ie flips all bits)
	valHolder = valHolder + 1; //gets 2s comp
	return valHolder;
}

long long int myPow(int index){
	long long int holdBit = 1;
	int i;
	
	if (index == 0){
		holdBit = 1; //ie (...0001)
	}
	else{
		for (i = 0; i < index; i++){
			holdBit *=  2;
		}
	}
	
	return holdBit;
}

void spff (char *sign, char *exponent, char *significand, float *src){
// not implemented
}

void dpff (char *sign, char *exponent, char *significand, double *src){
// not implemented
}
