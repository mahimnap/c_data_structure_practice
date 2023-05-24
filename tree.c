#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

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

void attachNode (struct Performance *performance, struct Node **node_ptr, void *src, unsigned int width){
	struct Node *newNode = (struct Node *) malloc (sizeof (struct Node));
	newNode->data = malloc (width); 
	if (newNode == NULL || newNode->data == NULL){
		fprintf (stderr, "%s", "Error with malloc in attachNode, exiting\n");
		exit (1); 
	}
	else {
		memcpy (newNode->data, src, width);  
		newNode->lt = NULL; 
		newNode->gte = NULL; 
		*node_ptr = newNode; 
		performance->mallocs += 1; 
		performance->writes += 1; 
	}
}

int comparNode (struct Performance *performance, struct Node **node_ptr, int (*compar) (const void *, const void *), void *target){
	int returnVal;
	returnVal = (*compar)(target, (*node_ptr)->data);
	performance->reads += 1; 
	return returnVal; 
}

struct Node **next (struct Performance *performance, struct Node **node_ptr, int direction){
	if (*node_ptr == NULL){
		fprintf (stderr, "%s", "Error root is NULL in next function, exiting\n");
		exit (1); 
	}
	else if (direction < 0){
		performance->reads += 1; 
		return &((*node_ptr)->lt);
	}
	else {
		performance->reads += 1; 
		return &((*node_ptr)->gte);
	}
}

void readNode (struct Performance *performance, struct Node **node_ptr, void *dest, unsigned int width){
	if (*node_ptr == NULL){
		fprintf (stderr, "%s", "Error root is NULL in readNode function, exiting\n");
		exit (1); 
	}
	else{
		memcpy (dest, (*node_ptr)->data, width); 
		performance->reads += 1; 
	}
}

void detachNode (struct Performance *performance, struct Node **node_ptr){
	if (*node_ptr == NULL){
		fprintf (stderr, "%s", "Error root is NULL in detachNode function, exiting\n");
		exit (1); 
	}
	else{
		free ((*node_ptr)->data); 
		free (*node_ptr); 
		*node_ptr = NULL; 
		performance->frees += 1; 
	}
}

int isEmpty (struct Performance *performance, struct Node **node_ptr){
	if (*node_ptr == NULL){
		return 1;
	}
	else {
		return 0;
	}
}

void addItem (struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *, const void *), void *src, unsigned int width){
	int compVal; 
	while (isEmpty (performance, node_ptr) != 1){
		compVal = comparNode (performance, node_ptr, compar, src); 
		node_ptr = next(performance, node_ptr, compVal); 
	}
	attachNode (performance, node_ptr, src, width); 
}

void freeTree (struct Performance *performance, struct Node **node_ptr){
	if (isEmpty (performance, node_ptr) != 1){
		freeTree (performance, next (performance, node_ptr, -1));
		freeTree (performance, next (performance, node_ptr, 1));
		detachNode (performance, node_ptr); 
	}
}

int searchItem (struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width){
	if (isEmpty(performance, node_ptr) != 1){
		if (comparNode(performance, node_ptr, compar, target) < 0){
			searchItem (performance, &((*node_ptr)->lt), compar, target, width); 
		}
		else if (comparNode(performance, node_ptr, compar, target) < 0){
			searchItem (performance, &((*node_ptr)->gte), compar, target, width); 
		}
		else {
			return 1; 
		}
	}
	return 0; 
}
