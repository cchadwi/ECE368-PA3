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

void swapPath(struct Path** x, struct Path** y)
{
    struct Path *temp = *x;
    *x = *y;
    *y = temp;
    return;
}