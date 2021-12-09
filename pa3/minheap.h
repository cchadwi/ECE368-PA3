#include <stdlib.h>
#include <limits.h>

struct Path
{
    int vertex;
    int path;
};

struct Path* newPath(int vertex, int path)
{
    struct Path* minHeapNode = (struct Path*)malloc(sizeof(struct Path));
    minHeapNode -> vertex = vertex;
    minHeapNode -> path = path;
    return(minHeapNode);
};

struct MinHeap
{
    int size;
    struct Path **array;
};

struct MinHeap* createHeap(int size)
{
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap -> array = (struct Path**)malloc(size * sizeof(struct Path*));
    minHeap -> size = 0;
    int i;

    for(i = 0; i < size; i++)
    {
        minHeap -> array[i] = newPath(i, INT_MAX);
        minHeap -> size += 1;
    }
    return(minHeap);
};

struct Path* extract(struct MinHeap* minHeap, int **pos, int length)
{
    if(minHeap -> size == 0)
    {
        retrn NULL;
    }
    struct Path* root = minHeap -> array[0];
    int prevPos = minHeap -> size - 1;
    struct Path* prevNode = minHeap -> array[prevPos];
    minHeap -> array[0] = prevNode;
    (*pos)[root -> vertex] = prevNode;
    (*pos)[prevNode -> vertex] = 0;
    minHeap -> size -= 1;
    downHeapify(minHeap, 0, pos, length);
};

void swapPath(struct Path** x, struct Path** y)
{
    struct Path *temp = *x;
    *x = *y;
    *y = temp;
    return;
}
