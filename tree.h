/*
 * Name: Mahimna Pyakuryal
 * Section: 0209
 * Student Number: 1014826
 * Assignment: CIS 2520 Assignment 4
 * Email ID: mpyakury
 */

#ifndef _TREE_H_
#define _TREE_H_

struct Node {
	void *data; 
	struct Node *lt; 
	struct Node *gte; 
}; 

struct Performance {
	unsigned int reads; 
	unsigned int writes; 
	unsigned int mallocs; 
	unsigned int frees; 
};

struct Performance *newPerformance();
/*same functionality as previous assignments
 */ 
void attachNode (struct Performance *performance, struct Node **node_ptr, void *src, unsigned int width);  
/*malloc memory for the new node to be added into tree and the data member of that node
 * if there is no error, copy the src passed in into the data member for the node 
 * set two children nodes for the new node to null 
 * increase performance mallocs and writes by 1
 */
int comparNode (struct Performance *performance, struct Node **node_ptr, int (*compar) (const void *, const void *), void *target); 
/* uses compar function passed in from main 
 * this can have three results (only two will matter for most functions except for search, which 
 * will use all three 
 * The three are: 
 * less than zero (use lt child) 
 * greater than zero (use gte child) 
 * equal to zero (use gte child, or search found for search function
 */
struct Node **next (struct Performance *performance, struct Node **node_ptr, int direction);
/*function will return the address of the pointer to the appropriate child 
 * determined by the previous comparNode function 
 * This function essentially just lets you traverse the tree
 */ 
void readNode (struct Performance *performance, struct Node **node_ptr, void *dest, unsigned int width); 
/*if the node isn't empty, copy the value at the node into dest
 */
void detachNode (struct Performance *performance, struct Node **node_ptr); 
/* if the node isn't empty, free data in the node, free the node itself and 
 * set node to NULL 
 */
int isEmpty (struct Performance *performance, struct Node **node_ptr);
/* if node pointed to by node_ptr is empty return 1 (true) else return 0 (false) 
 */
void addItem (struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *, const void *), void *src, unsigned int width);  
/* while there are still nodes, traverse list using next and comparNode
 * once at the final node, leave the loop (looping with isEmpty) 
 * use attachNode at this final node to add the item
 */
void freeTree (struct Performance *performance, struct Node **node_ptr); 
/* if isEmpty is false recursively free any present children nodes
 * then once the children are freed recursively it will destroy other recursions 
 * and finally delete the root itself
 */
int searchItem (struct Performance *performance, struct Node **node_ptr, int (*compar)(const void *, const void *), void *target, unsigned int width);
/* this will recursively traverse list based on returns of compar function 
 * 0 = found, return 1
 * x > 0 = take gte path 
 * x < 0 = take lt path
 * if nothing is found through all recursion, return 0
 */

#endif 
