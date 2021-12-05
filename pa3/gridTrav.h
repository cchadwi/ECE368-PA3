#ifndef gridTrav
#define gridTrav
#include <stdlib.h>

struct GridTrav
{
	struct TraversalNode *head;
}

struct TraversalNode
{
	int path;
	int weight;
	struct TraversalNode *next;
}

struct TraversalNode* newGridNode(int path, int weight)
{
	struct TraversalNode *newNode = malloc(sizeof(struct TraversalNode));
	newNode -> path = path;
	newNode -> weight = weight;
	newNode -> next = NULL;
	return(newNode);
}

#endif