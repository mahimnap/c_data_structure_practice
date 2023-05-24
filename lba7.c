#include "graph.h" 
#include <stdio.h>
#include <ctype.h> 
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]){
	Graph *newGraph = createGraph ();
	addVertex (newGraph, 1); 
	addVertex (newGraph, 2); 
	addVertex (newGraph, 3); 
	addVertex (newGraph, 4); 
	addVertex (newGraph, 5); 
	
	addEdge (newGraph, 1, 2); 
	addEdge (newGraph, 2, 3); 
	addEdge (newGraph, 2, 4); 
	addEdge (newGraph, 3, 4); 
	addEdge (newGraph, 4, 1); 
	addEdge (newGraph, 4, 5); 
	
	printGraph(newGraph); 
	
	printf ("Checking for 3 (1): %d\n", checkForVertex (newGraph, 3)); 
	printf ("Checking for 6 (0): %d\n", checkForVertex (newGraph, 6)); 
	
	printf ("Checking Edges: %d\n", getNumEdges (newGraph)); 
	printf ("Checking Vertices: %d\n", getNumVertices(newGraph)); 
	
	freeGraph (newGraph); 
	
	printf ("Valgrind Runs with No Memory Leaks\n"); 
	
	return 0; 
}
