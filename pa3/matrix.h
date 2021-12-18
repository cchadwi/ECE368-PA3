#ifndef matrix
#define matrix
#include "adjList.h"
#include <stdlib.h>

struct Matrix
{
	int numV;
	struct AdjList* list; 
};

struct Matrix* createGraph(int numV)
{
	struct Matrix* graph = malloc(sizeof(struct Matrix));
	graph -> numV = numV;
	graph -> list = malloc(numV * sizeof(struct AdjList));

    int i;
	for (i = 0; i < numV; ++i) 
	{
		graph -> list[i].head = NULL;
	}

	return graph;
};

void addEdge(struct Matrix* graph, int src, int dest, int weight)
{
	struct AdjacencyNode* newNode = newListNode(dest, weight);
	newNode -> next = graph -> list[src].head;
	graph -> list[src].head = newNode;
};

#endif