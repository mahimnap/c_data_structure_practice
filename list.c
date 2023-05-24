#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

//comments in headers to improve readability

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

void push (struct Performance  *performance, struct Node **list_ptr, void *src, unsigned int width){
	struct Node *newNode = (struct Node *)malloc(sizeof (struct Node));
	newNode->data = malloc(width);
	if ((newNode == NULL) || (newNode->data == NULL)){
		fprintf (stderr, "%s", "Error with malloc in push, exiting");
		exit (1); 
	}
	memcpy (newNode->data, src, width);
	newNode->next = *list_ptr;
	*list_ptr = newNode;
	performance->mallocs += 1;
	performance->writes += 1;
}

void readHead (struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width){
	if (*list_ptr == NULL){
		fprintf (stderr, "%s", "Inputted empty list into readHead, exiting"); 
		exit (1); 
	}
	memcpy (dest, (*list_ptr)->data, width);
	performance->reads += 1;
}

void pop (struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width){
	if (*list_ptr == NULL){
		fprintf (stderr, "%s", "Inputted empty list into pop, exiting");
		exit (1);
	}
	struct Node *holder = *list_ptr; 
	*list_ptr = holder->next;
	memcpy (dest, holder->data, width); 
	free (holder->data);
	free (holder);
	performance->frees += 1;
	performance->reads += 1;
}

struct Node **next(struct Performance *performance, struct Node **list_ptr){
	if (*list_ptr == NULL){
		fprintf (stderr, "%s", "Inputted empty list into next, exiting");
		exit (1);
	}
	performance->reads += 1;
	return &((*list_ptr)->next);
}

int isEmpty (struct Performance *performance, struct Node **list_ptr){
	if (*list_ptr == NULL){
		return 1;
	}
	else {
		return 0;
	}
}

void freeList (struct Performance *performance, struct Node **list_ptr){
	unsigned char *trash = NULL;
	while (isEmpty (performance, list_ptr) != 1){
		pop (performance, list_ptr, trash, 0);
	}
}

void readItem (struct Performance *performance, struct Node **list_ptr, unsigned int index, void *dest, unsigned int width){
	int i; 
	for (i = 0; i <= index; i++){
		if (i == index){
			readHead (performance, list_ptr, dest, width);
			return; 
		}
		list_ptr = next (performance, list_ptr);
	}
}

void appendItem (struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width){
	while (isEmpty (performance, list_ptr) != 1) {
		list_ptr = next(performance, list_ptr);
	}
	push (performance, list_ptr, src, width);
}

void insertItem (struct Performance *performance, struct Node **list_ptr, unsigned int index, void *src, unsigned int width){
	for (int i = 0; i <= index; i++){
		if (i == index){
			push(performance, list_ptr, src, width);
			return; 
		}
		list_ptr = next(performance, list_ptr);
	}
}

void prependItem(struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width){
	insertItem (performance, list_ptr, 0, src, width);
}

void deleteItem (struct Performance *performance, struct Node **list_ptr, unsigned int index){
	void *trash = NULL;
	for (int i = 0; i <= index; i++){
		if (i == index){
			pop(performance, list_ptr, trash, 0);
		}
		list_ptr = next (performance, list_ptr);
	}
}

int findItem (struct Performance *performance, struct Node **list_ptr, int (*compar)(const void*, const void*), void *target, unsigned int width){
	void *holder = malloc (width); 
	int comp; 
	int i = 0; 
	while (isEmpty (performance, list_ptr) != 1){ 
		readHead (performance, list_ptr, holder, width);
		comp = (*compar)(holder, target);
		if (comp == 0){
			comp = i; 
			break; 
		}
		else{
			comp = -1; 
			list_ptr = next (performance, list_ptr);
			i++; 
		}
	}
	return comp; 
}
