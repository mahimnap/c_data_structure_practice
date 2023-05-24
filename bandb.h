/*
 * CIS 2520 (0101) Assignment 1
 * Mahimna Pyakuryal
 * 1014826
 * mpyakury
 * 
 */
#ifndef protos
#define protos

void getbytes(unsigned char dest[], int bytes, void *src, int reverse); 
/*received a destination, source, bytes to be copied and a reverse val
 * if reverse isn't true, copy all bytes from src directly 
 * to dest using memcpy
 * if it is set, use a char pointer 
 * point to src, then increment all the way
 * to (bytes - 1) - ie byte index value
 * decrement through new pointer at the end of the source address
 * store chars in destination as you decrement
 */

void getbits (char dest[], int bytes, void *src, int start, int end);
/*
 * uses bytes, start, and end values to determine 
 * both index position and bit position
 * quotient = x/8
 * index: (bytes) - quotient - 1
 * bit position: x%/8
 * these value are then used to shift >>
 * the binary representation to end of bits 
 * and store the '1' or '0' respresented by the 
 * value in the destion
 */

unsigned long long bits2ull (char *bits);
/*function will recieve a string of '0' and '1'
 * that represent a value in binary
 * that value is then converted into 
 * decimal using and passed through as 
 * an unsigned long long int
 */

long long bits2ll (char *bits);
/*function will receive a string of '0' and '1'
 * that represent a value in binary
 * and pass through that binary values 
 * 2s complement in decimal notation (~)
 */

long long int myPow(int index);
/*returns the value of a bit at a given index 
 * e.g. index = 5 = (2^5) = 32
 * this logic is used in multiple functions so addded into function
 * for modularity purposes
 * It helps convert a binary representation of chars of '1' and '0'
 * into decimal 
 */

void spff (char *sign, char *exponent, char *significand, float *src);
//implement asap

void dpff (char *sign, char *exponent, char *significand, double *src);
//implement asap

#endif
