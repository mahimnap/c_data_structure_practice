#ifndef _HASH_H_ 
#define _HASH_H_

struct HashTable
{
	unsigned int capacity; 
	unsigned int nel; 
	void **data; 
	int (*hash) (void *, int);
	int (*compar) (const void*, const void *);
};

struct Performance 
{
	unsigned int reads; 
	unsigned int writes; 
	unsigned int mallocs; 
	unsigned int frees; 
};

struct Performance *newPerformance (); 
struct HashTable *createTable (struct Performance *performance, unsigned int capacity, int (*hash)(void*, int), int (*compar)(const void*, const void*));
void addElement (struct Performance *performance, struct HashTable *table, void *src); 
int getIdx (struct Performance *performance, struct HashTable *table, void *src); 
void freeTable (struct Performance *performance, struct HashTable *table); 
void *getElement (struct Performance *performance, struct HashTable *table, void *src); 
void removeElement (struct Performance *performance, struct HashTable *table, void *target);
int hashAccuracy (struct HashTable *table); 
void rehash (struct HashTable *table); 

/*improvements: 
 * Get rid of holder to increment because you can just directly access elements through table->data[i]
 * - can view this as register address with displacement in assembly 
 * - check if you did this in previous assignments too (i don think I did) 
 */
#endif 
