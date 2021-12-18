#ifndef adjList
#define adjList
#include <stdlib.h>

struct AdjList
{
	struct AdjacencyNode *head;
};

struct AdjacencyNode
{
	int dest;
	int weight;
	struct AdjacencyNode* next;
};

struct AdjacencyNode* newListNode(int dest, int weight)
{
	struct AdjacencyNode* newNode = malloc(sizeof(struct AdjacencyNode));
	newNode->dest = dest;
	newNode->weight = weight;
	newNode->next = NULL;
	return newNode;
};

#endif