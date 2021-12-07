#ifndef pathTrav
#define pathTrav
#include <stdlib.h>

struct PathTrav
{
	struct TraversalNode *head;
};

struct TraversalNode
{
	int path;
	int weight;
	struct TraversalNode *next;
};

struct TraversalNode* newListNode(int path, int weight)
{
	struct TraversalNode *newNode = malloc(sizeof(struct TraversalNode));
	newNode -> path = path;
	newNode -> weight = weight;
	newNode -> next = NULL;
	return(newNode);
};

#endif