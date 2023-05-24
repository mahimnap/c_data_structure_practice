#include "graph.h" 
#include <stdio.h>
#include <ctype.h> 
#include <stdlib.h>
#include <string.h>
	
Graph* createGraph(){
	Graph *retGraph;
	retGraph = (Graph *) malloc (sizeof (Graph)); 
	retGraph->numVertices = 0; 
	retGraph->numEdges = 0; 
	retGraph->vertexList = NULL; 
	return retGraph;
}

Vertex* createVertex (int value){
	Vertex *retVert; 
	retVert = (Vertex *) malloc (sizeof (Vertex)); 
	retVert->value = value; 
	retVert->adjList = NULL; 
	retVert->next = NULL; 
	return retVert; 
}

AdjVertex* createAdjVertex (int value){
	AdjVertex *retAdj;
	retAdj = (AdjVertex *) malloc (sizeof(AdjVertex));
	retAdj->value = value; 
	retAdj->next = NULL; 
	return retAdj; 
}

void addVertex (Graph *graph, int value){
	Vertex **iterator = &(graph->vertexList);
	while (*iterator){
		iterator = &((*iterator)->next);
	}
	*iterator = createVertex (value);
	graph->numVertices += 1; 
}

void addAdjVertex (Vertex *vertex, int value){
	AdjVertex **iterator = &(vertex->adjList); 
	while (*iterator){
		iterator = &((*iterator)->next);
	}
	*iterator = createAdjVertex (value); 
}

void addEdge (Graph *graph, int vertex1, int vertex2){
	Vertex **iterator = &(graph->vertexList); 
	for (int i = 0; i < graph->numVertices; i++){
		if ((*iterator)->value == vertex1){
			addAdjVertex (*iterator, vertex2); 
			graph->numEdges += 1; 
		}
		if ((*iterator)->value == vertex2){
			addAdjVertex (*iterator, vertex1); 
			graph->numEdges += 1; 
		}
		iterator = &((*iterator)->next); 
	}
}

void printGraph (Graph *graph){ 
	Vertex **iterator = &(graph->vertexList); 
	AdjVertex **iterator2; 
	for (int i = 0; i < graph->numVertices; i++){
		printf ("Vertex: %d |", (*iterator)->value); 
		iterator2 = &((*iterator)->adjList); 
		
		while (*iterator2){
			printf (" %d ", ((*iterator2)->value)); 
			iterator2 = &((*iterator2)->next); 
		}
		printf ("\n"); 
		iterator = &((*iterator)->next);
	}
}

int checkForVertex (Graph *graph, int src){
	Vertex **iterator = &(graph->vertexList); 
	for (int i = 0; i < graph->numVertices; i++){
		if ((*iterator)->value == src){
			return 1; 
		}
		iterator = &((*iterator)->next);
	}
	return 0; 
}

int getNumVertices (Graph *graph){
	return graph->numVertices;
}

int getNumEdges (Graph *graph){
	return graph->numEdges; 
}

void freeGraph (Graph *graph){
	freeVertexList(graph->vertexList);
	free (graph); 
}

void freeVertexList (Vertex *node){
	if (node){
		freeVertexList (node->next); 
		freeAdjVertexList (node->adjList); 
		free (node); 
	}
}

void freeAdjVertexList (AdjVertex *list){
	if (list){
		freeAdjVertexList (list->next);
		free(list); 
	}
}

/* Questions 
 * 
 * What was the point of writing getNumVertices/getNumEdges
 * It's already kept track of in the graph struct 
 * 
 * print function is still printing after recursive free calls 
 * 
 * Were the free functions done how they wanted
 * 
 * Edge counting is wrong. Should there be an if-else in the 
 * addEdge function instead? 
 * 
 * create AdjVertexList says to set list to null -> probably a mistake
 * 
 * Is there a way to do this without double pointers? 
 * Malloc maybe? -> would this be less efficient? 
 * 
 * ask about 2316 output, pretty sure it should be 2315 
 * because 6 isn't a vertice in the testing portion
 */ 
