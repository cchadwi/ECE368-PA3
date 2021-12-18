#ifndef matrix
#define matrix
#include "adjList.h"
#include <stdlib.h>

struct Matrix 
{
    int numV;
    struct AdjList* list;
};

struct Matrix* createGrid(int numV)
{
    struct Matrix* grid = malloc(sizeof(struct Matrix));
    grid->numV = numV;
    grid->list = malloc(numV * sizeof(struct AdjList));
    int i;

    for(i = 0; i < numV; i++)
    {
        grid -> list[i].head = NULL;
    }
    return grid;
};

void addEdge(struct Matrix* grid, int src, int path, int weight)
{
    struct AdjacencyNode* newNode = newListNode(path, weight);
    newNode -> next = grid->list[src].head;
    grid -> list[src].head = newNode;
};

#endif