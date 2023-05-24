#ifndef _GRAPH_H_
#define _GRAPH_H_

typedef struct adjVertex {
	int value; 
	struct adjVertex *next; //holds next adjacent vertex (use for iteration) 
} AdjVertex; 

typedef struct vertex {
	int value; 
	AdjVertex *adjList; //head node for all adjacent vertexes within a vertex 
	struct vertex *next; //holds next vertex (use for iteration)
} Vertex; 

typedef struct graph {
	int numVertices; 
	int numEdges; 
	Vertex *vertexList; //head node for vertexes
} Graph; 

Graph* createGraph(); 
Vertex* createVertex (int value); 
AdjVertex* createAdjVertex (int value); //changed name and functions 
void addVertex (Graph *graph, int value); 
void addAdjVertex (Vertex *vertex, int value);
void addEdge (Graph *graph, int vertex1, int vertex2); 
void printGraph (Graph *graph); 
int checkForVertex (Graph *graph, int src);
int getNumVertices (Graph *graph);
int getNumEdges (Graph *graph); 
void freeGraph (Graph *graph);
void freeVertexList (Vertex *node);
void freeAdjVertexList (AdjVertex *list); 

	

#endif
