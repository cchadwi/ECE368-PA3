#ifndef matrix
#define matrix
#include "pathTrav.h"
#include <stdlib.h>

struct Matrix 
{
    int numV;
    struct PathTrav* list;
};

struct Matrix* createGrid(int numV)
{
    struct Matrix* grid = malloc(sizeof(struct Matrix));
    grid->numV = numV;
    grid->list = malloc(numV * sizeof(struct PathTrav));
    int i;

    for(i = 0; i < numV; i++)
    {
        grid -> list[i].head = NULL;
    }
    return grid;
};

void addEdge(struct Matrix* grid, int src, int path, int weight)
{
    struct TraversalNode* newNode = newListNode(path, weight);
    newNode -> next = grid->list[src].head;
    grid -> list[src].head = newNode;
}

#endif