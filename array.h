/* Name: Mahimna Pyakuryal
 * Section: 0209
 * Student Number: 1014826
 * Assignment: CIS 2520 Assignment 2
 * Email ID: mpyakury
 */

#ifndef _array_h 
#define _array_h

struct Array
{
	unsigned int width;
	unsigned int nel; 
	unsigned int capacity;
	void *data;
};

struct Performance
{
	unsigned int reads;
	unsigned int writes;
	unsigned int mallocs; 
	unsigned int frees; 
};

struct Performance *newPerformance();
/*This function initializes the values for a pointer to struct Performance
 */

struct Array *newArray(struct Performance *performance, unsigned int width, unsigned int capacity); 
/*This function passes through a struct pointer performance, width to set data width, and capacity
 * to set maximum capacity in the struct members
 */

void readItem (struct Performance *performance, struct Array *array, unsigned int index, void *dest);
/*This function reads retrieves data stored at the given index for the user-determined 
 * data type. It stores the data retrieved at the given index into the void pointer dest 
 * NOTE: void pointer used because working with various data types
 */

void writeItem (struct Performance *performance, struct Array *array, unsigned int index, void *src);
/*this function will write a value into the given index
 */

void contract (struct Performance *performance, struct Array *array); 
/*this function will contract the array by decreasing array->nel by 1 
 */

void freeArray (struct Performance *performance, struct Array *array);
/* this function will free the malloced space in array->data (ie array)
 * and the space in the malloced space addressed to the struct pointer itself
 */

void appendItem (struct Performance *performance, struct Array *array, void *src); 
/*this will add an item to the end of the array. This will add an element 1 index beyond
 * the last element in the array. The size is increased by writeItem and is not 
 * something that is delt with here
 */

void insertItem (struct Performance *performance, struct Array *array, unsigned int index, void *src);
/*this will expand the array by 1, copy the data over 1 element to the right starting at the
 * index provided then insert the desired value in the desired location
 */

void prependItem (struct Performance *performance, struct Array *array, void *src);
/*This function is the same as insertItem (just one line that calls insertItem) except 
 * it will only insert items at the first index of the arrayt
 */

void deleteItem (struct Performance *performance, struct Array *array, unsigned int index);
/*This function will  shift every value to the right of the index 1 to the left thus 
 * deleting the item in the desired array. It is then contracted to delete the 
 * duplicate value
 */

int findItem (struct Performance *performance, struct Array *array, int (*compar) (const void*, const void*), void *target);
/* this function will perform a linear search through the array and return the index if the value is found
 */

int searchItem (struct Performance *performance, struct Array *array, int (*compar)(const void*, const void*), void *target);
/*this function will perform a binary search through the array. This entails 
 */

#endif
