#ifndef adjList
#define adjList
#include <stdlib.h>

struct AdjList
{
	struct AdjacencyNode *head;
};

struct AdjacencyNode
{
	int path;
	int weight;
	struct AdjacencyNode *next;
};

struct AdjacencyNode* newListNode(int path, int weight)
{
	struct AdjacencyNode* newNode = malloc(sizeof(struct AdjacencyNode));
	newNode -> path = path;
	newNode -> weight = weight;
	newNode -> next = NULL;
	return newNode;
};

#endif