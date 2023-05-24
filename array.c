#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "array.h"

//comments and information all in header file to help maintain good readability

struct Performance *newPerformance(){ 
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

struct Array *newArray(struct Performance *performance, unsigned int width, unsigned int capacity){
	struct Array *returnArr = (struct Array *) malloc (sizeof (struct Array)); 
	void* ptr = malloc(width*capacity);
	if ((returnArr == NULL) || (ptr == NULL)){
		fprintf (stderr, "%s", "Error: Malloc Failed. Exiting\n");
		exit (1);
	}
	else{
		returnArr->data = ptr; 
		returnArr->width = width; 
		returnArr->capacity = capacity; 
		returnArr->nel = 0;
		performance->mallocs += 1;
	}
	return returnArr;
}

void readItem (struct Performance *performance, struct Array *array, unsigned int index, void *dest){ //check edge ranges for this
	void *holder = array->data;
	if (index >= (array->nel)){
		fprintf (stderr, "%s", "Error: readItem Failed. Exiting\n\n");
		exit (1);
	}
	else{
		holder = (unsigned char*)holder + ((index) * array->width); 
		memcpy(dest, holder, array->width);
		performance->reads += 1;
	}
}

void writeItem (struct Performance *performance, struct Array *array, unsigned int index, void *src){
	void *holder = array->data;
	if ((index > array->nel) || (index >= array->capacity)){
		fprintf (stderr, "%s", "Error: writeItem Failed. Exiting\n");
		exit (1);
	}
	else{ 
		holder = (unsigned char *)holder + ((index) * (array->width));
		memcpy (holder, src, array->width); 
		performance->writes += 1; 
		if (index == array->nel){
			array->nel += 1;
		}
	}
}

void contract (struct Performance *performance, struct Array *array){
	if (array->nel == 0){
		fprintf (stderr, "%s", "Error: contract Failed. Exiting\n");
	}
	else{
		array->nel -= 1;
	}
}

void freeArray (struct Performance *performance, struct Array *array){
	free (array->data); 
	free (array); 
	performance->frees += 1; 
}

void appendItem (struct Performance *performance, struct Array *array, void *src){
	writeItem (performance, array, array->nel, src);
}

void insertItem (struct Performance *performance, struct Array *array, unsigned int index, void *src){
	unsigned char *holder = (unsigned char *) malloc ((sizeof(char)) * array->width);
	int i; 
	for (i = array->nel; i > index; i--){
		readItem (performance, array, i - 1, holder);
		writeItem (performance, array, i, holder);
	}
	writeItem (performance, array, index, src);
	free (holder);
}

void prependItem (struct Performance *performance, struct Array *array, void *src){
	insertItem (performance, array, 0, src);
}

void deleteItem (struct Performance *performance, struct Array *array, unsigned int index){
	unsigned char *holder = (unsigned char *) malloc ((sizeof(char)) * array->width);
	int i;
	for (i = index; i < ((array->nel) - 1); i++){
		readItem (performance, array, i + 1, holder);
		writeItem (performance, array, i, holder);
	}
	contract (performance, array);
}

int findItem (struct Performance *performance, struct Array *array, int (*compar) (const void*, const void*), void *target){ 
	unsigned char *holder = (unsigned char *) malloc (sizeof(char) * array->width);
	int i;
	int comp;
	for (i = 0; i < array->nel; i++){
		readItem (performance, array, i, holder);
		comp = (*compar)((void*)holder, target);
		if (comp == 0){
			comp = i;
			break;
		}
		else {
			comp = -1;
		}
	}
	free (holder);
	return comp;
}

int searchItem (struct Performance *performance, struct Array *array, int (*compar)(const void*, const void*), void *target){
	int i;
	int comp;
	int divIdx = (array->nel - 1) / 2;
	unsigned char *holder = (unsigned char *) malloc (sizeof(char) * array->width);
	for (i = divIdx; i < array->nel; i++){
		readItem (performance, array, i, holder);
		comp = (*compar)((void*)holder, target);
		if (comp == 0){
			comp = i;
			break;
		}
		else{
			comp = -1;
		}
	}
	
	if (comp == -1){
		for (i = 0; i < divIdx; i++){
			readItem (performance, array, i, holder);
			comp = (*compar)((void*)holder, target);
			if (comp == 0){
				comp = i; 
				break;
			}
			else {
				comp = -1; 
			}
		}
	}
	free (holder);
	return comp;
}
