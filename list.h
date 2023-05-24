/*
 * Name: Mahimna Pyakuryal
 * Section: 0209
 * Student Number: 1014826
 * Assignment: CIS 2520 Assignment 3
 * Email ID: mpyakury
 */

#ifndef _LIST_H_
#define _LIST_H_ 

struct Node
{
	void *data;
	struct Node *next; 
};
/*
 * struct for nodes of linked list
 * data holds a value of any user defined data type 
 * next points to next node in the list
 * don't forget to initialize the head pointer in main file with NULL 
 * to allow checking for NULL throughout code 
 * This NULL will continue to be pushed back so this will be useful 
 * throughout code to determine when list is at the end
 */
struct Performance
{
	unsigned int reads;
	unsigned int writes;
	unsigned int mallocs; 
	unsigned int frees; 
};
/*
 * same as a2 
 * used to keep track of performance of linked lists in order to compare with previous and future assignments 
 */
struct Performance *newPerformance();
/*
 * Creates a new pointer to a struct that will keep track reads, writes, mallocs, and frees that are performed through 
 * various actions taken with the linked list
 * (same functionality as A2) -> useful for comparing the 2 performances for strengths and weaknesses 
 * of linked lists vs. arrays
 */
void push (struct Performance  *performance, struct Node **list_ptr, void *src, unsigned int width); 
/*
 * malloc space for a new head to be added to where old head used to be (or set head if list is currently empty) 
 * allocate space for the data member of the struct based off the size of the data being passed in (ie width) 
 * if either malloc statements fail, exit
 * memcpy the data from the source into the location of memory allocated for data in the node based on size width (ie data type)
 * dereference the double pointer in order to have the head point to the new node created (*list_ptr = head)
 * a double pointer is used here (pass by reference) in order to be able to accomplish this 
 * adding a node, so increase writes by 1
 * mallocing a node, so increase mallocs by 1
 */
void readHead (struct Performance *performance, struct Node **list_ptr, void *dest, unsigned int width);
/* 
 * if the head of the node is NULL (ie *list_ptr) then exit  (ie if list is empty) 
 * if not, copy the data in the node into the destination passed in
 * reading once so increase reads by 1 
 */ 
void pop (struct Performance *performance, struct Node **list_ptr, void *dest, unsigned width);
/*
 * if the head node is NULL then exit (ie if list is empty) 
 * use a holder node to be able to set the current head to the next node (*list_ptr = holder->next) 
 * copy the data from the holder node into destination in case user needs  to save this otherwise lost data
 * free the data in holder 
 * free the holder nodes itself 
 * freeing so increase frees 
 * reading head so increase reads
 */
struct Node **next(struct Performance *performance, struct Node **list_ptr);
/* 
 * if head node is null exit (ie if list is empty) 
 * if not increase reads by one 
 * return the & of the pointer to the pointer that points to the next node of the list (->next)
 * Required & because returning a double pointer in order to be able to use with other functions (**list_ptr) 
 */ 
int isEmpty (struct Performance *performance, struct Node **list_ptr);
/*
 * if the head is null (ie list is empty) return 1 else return 0 
 */
void freeList (struct Performance *performance, struct Node **list_ptr);
/* create a trash pointer to use with pop because return data isn't needed -> could've just used void * but it doesn't really matter regardless
 * while the list isn't empty (use isEmpty in a while loop till you reach the end) 
 * pop each head off (pass in 0, memcpy will ignore the statement if 0 bytes are being copied)
 */
void readItem (struct Performance *performance, struct Node **list_ptr, unsigned int index, void *dest, unsigned int width);
/*
 * loop till index is reached
 * traversal of list is done through next function 
 * once index is reached, readHead
 */
void appendItem (struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width);
/*
 * traverse the list (next function) while the head of the traversed pointer isn't empty 
 * once you get there, exit loop and push src into that header based on data type (width) 
 */
void insertItem (struct Performance *performance, struct Node **list_ptr, unsigned int index, void *src, unsigned int width);
/*
 * traverse, once index is reached, push item on ->didn't need 'return', loop woudl've stopped regardless
 */
void prependItem(struct Performance *performance, struct Node **list_ptr, void *src, unsigned int width);
/* 
 * insertItem at position 0
 */
void deleteItem (struct Performance *performance, struct Node **list_ptr, unsigned int index); 
/*
 * traverse, once index is reached, pop
 */
int findItem (struct Performance *performance, struct Node **list_ptr, int (*compar)(const void*, const void*), void *target, unsigned int width);
/*
 * set a compar function in main that compares the relevant data types and returns a 0 if they match
 * use readHead to retrieve each item, while traversing list, to send back into function in main to compare two values
 * if the comparison comes back as true, set the index to i and break out of the loop 
 * if it doesn't come back as true by the end of the list, set the return value to -1
 */

#endif 
