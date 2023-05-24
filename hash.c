/*
 * Mahimna Pyakuryal
 * 1014826
 * CIS 2520
 * Assignment 5
 */

#include <stdio.h> 
#include <stdlib.h> 
#include <ctype.h> 
#include <string.h> 
#include "hash.h" 

struct Performance *newPerformance (){ 
	struct Performance *returnVal = (struct Performance *)malloc(sizeof(struct Performance));
	if (returnVal == NULL){
		fprintf (stderr, "%s", "Error: Malloc Failed. Exiting\n");
		exit(1);
	}
	else{ 
		returnVal->reads = 0;
		returnVal->writes = 0;
		returnVal->mallocs = 0;
		returnVal->frees = 0;
	}
	return returnVal;
}
struct HashTable *createTable (struct Performance *performance, 
								unsigned int capacity, 
								int (*hash)(void*, int), 
								int (*compar)(const void*, const void*)){									
	struct HashTable *newTable = (struct HashTable *) malloc (sizeof (struct HashTable)); 
	newTable->data = (void **) malloc ((sizeof (void*)) * capacity); //**data now address to location of capcity * pointers amount of memory 
	void **holder = newTable->data; 
	if (newTable == NULL || newTable->data == NULL){ 
		//if either address is not set (which it should be because mallocs obviously returns an addres to block of mem) 
		fprintf (stderr, "%s", "Error: Malloc Failed. Exiting\n");
		exit(1);
	}
	newTable->capacity = capacity; 
	newTable->nel = 0; 
	newTable->compar = compar; 
	newTable->hash = hash; 
	for (int i = 0; i < newTable->capacity; i++){
		*holder = NULL; //set every pointer in table to NULL 
		holder++; //increment to next pointer in double pointer array
		performance->reads += 1; 
	}
	performance->mallocs += 1; 
	return newTable; 
}

void addElement (struct Performance *performance, struct HashTable *table, void *src){
	int hashVal; 
	int idxCnt; //must be less than capacity 
	int i; //declared here because it will be used to set idxCnt 
	void **holder = table->data; 
	if (table->nel == table->capacity){ 
		//this will ensure while loop below doesn't get stuck in infinite loop as space must be available if this passes 
		fprintf (stderr, "%s", "Hash Table is Full. Exiting\n");
		exit(1);
	}
	hashVal = table->hash (src, table->capacity); //cast LATER if anything but an int type hash val is returned (long/short) 
	for (i = 0; i < hashVal; i++){ //will increment holder to point at hash value (element to store val at) 
		holder++; 
	}
	idxCnt = i; //idx counter to see if end of array is reached
	while (*holder != NULL){ //if current pointer already has something stored keep incrementing double pointer till it's at a pointer that's NULL 
		holder++; 
		idxCnt++; 
		performance->reads += 1; 
		if (idxCnt == table->capacity){ //if you reach the end, start searching again from the beginning 
			holder = table->data; 
			idxCnt = 0; 
		}
	}
	*holder = src; 
	table->nel += 1; 
	performance->writes += 1; 
}

int getIdx (struct Performance *performance, struct HashTable *table, void *src) {
	int hashHolder = table->hash (src, table->capacity); 
	int i = 0;  
	int idxCnt; 
	int comparRet = -1; 
	void **holder; 
	holder = table->data; 
	for (i = 0; i < hashHolder; i++){ //sets current value pointed to, to the hashVal
		holder++; 
	}
	idxCnt = i; 
	while (comparRet != 0){ //currently a use less condition 
		if (idxCnt == table->capacity){ //if you reach the end, start searching again from the beginning (never true on first iteration) 
			holder = table->data; 
			idxCnt = 0; 
		}
		if (*holder == NULL){
			comparRet = -1; 
			performance->reads += 1; //not 100% if i need this because it says only increment for compar usage 
		}
		else{ 
			comparRet = table->compar(*holder, src); 
			performance->reads += 1; 
			if (comparRet == 0){
				return idxCnt; 
			}
		}
		holder++; 
		idxCnt++; 
		if (idxCnt == hashHolder){ 
			//if next element to be read in next iteration of while loop is the original index, 
			//return -1 (idx not found) on the initial loop, it would've already exited if hash value was correct location 
			return -1;  
		}
	}
	return -1; 
}

void freeTable (struct Performance *performance, struct HashTable *table){
	free (table->data); 
	free (table); 
	performance->frees += 1; 
}

void *getElement (struct Performance *performance, struct HashTable *table, void *src){
	int idxRet = getIdx (performance, table, src); 
	void **holder = table->data; 
	if (idxRet == -1){
		return NULL; 
	}
	for (int i = 0; i < idxRet; i++){
		holder++; 
	}
	return *holder; 
}
 
void removeElement (struct Performance *performance, struct HashTable *table, void *target){
	int idxRet = getIdx (performance, table, target); 
	void **holder = table->data; 
	if (idxRet == -1){ //target to remove isn't in the table just exit 
		return; 
	} 
	for (int i = 0; i < idxRet; i++){
		holder++; 
	}
	*holder = NULL; 
	performance->writes += 1; 
	table->nel -= 1; 
}

int hashAccuracy (struct HashTable *table){ 
	void **holder = table->data; 
	int hashAcc = 0; 
	int hashVal; 
	for (int i = 0; i < table->capacity; i++){
		//do what needs to be done here
		if (*holder != NULL){ //if hash = i then perfect accuracy, otherwise do math 
			hashVal = table->hash(*holder, table->capacity); 
			if (i < hashVal){ //index is less than hash val ie looped back to start of array when linear probing 
				hashAcc += (table->capacity - hashVal) + i;
			}
			else{ //stored ahead of hashVal during linear probe (0 if the index is stored at hashval (x - x = 0))
				hashAcc += i - hashVal; 
			}
		}
		holder++; 
	}
	return hashAcc; 
}

void rehash (struct HashTable *table){
	int hashVal; 
	int i, j; 
	int cap;
	for (i = 0; i < table->capacity; i++){ //loop through entire hash table 
		if (table->data[i] != NULL){ //if a value is found 
			hashVal = table->hash(table->data[i], table->capacity); //get the hash value (ie ideal location if no collisons occur) 
			if (i > hashVal){ //ie stored ahead in table during linear probing 
				for (int j = hashVal; j < i; j++){ 
					if (table->data[j] == NULL){//same logic as below 
						table->data[j] = table->data[i]; 
						table->data[i] = NULL; 
						break;
					}
				}
			}
			else if (i < hashVal){ 
				//ie linear probing resulted in the value being looped back to beginning and stored at some point before hash value
				cap = table->capacity; 
				for (j = hashVal; j < cap; j++){ //loop from hashVal (ideal spot) to end of array 
					if (table->data[j] == NULL){ //if empty space is found (before currently stored spot), move value there
						table->data[j] = table->data[i]; //moving value to new spot 
						table->data[i] = NULL; //erase from old index 
						break; 
					}
					if (j == table->capacity){ //if the end of the table is reached 
						j = 0; //start search from start of table 
						cap = i; //search till where it's currently stored 
					}
				}
			}
		}
	}
}
