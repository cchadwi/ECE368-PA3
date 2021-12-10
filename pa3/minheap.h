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
    return minHeapNode;
};

struct MinHeap
{
    int size;
    struct Path **array;
};

struct MinHeap* makeHeap(int size)
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
    return minHeap;
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

    downHeapify(minHeap, pos, length, 0);
    return root;
};

void swapPath(struct Path** x, struct Path** y)
{
    struct Path *temp = *x;
    *x = *y;
    *y = temp;
    return;
}

void downHeapify(struct MinHeap* minHeap, int **pos, int length, int index)
{
    int smallest;
    int left;
    int right;
    struct Path *smallestNode;
    struct Path *indexNode;
    
    smallest = index;
    left = 2 * index + 1;
    right = 2 * index + 2;
    
    int size = minHeap -> size;
    int shortPath = minHeap -> array[smallest] -> path;

    if(minHeap -> array[left] -> path < shortPath && left < size)
    {
        if(minHeap -> array[left] -> path < shortPath)
        {
            smallest = left;
        }
        else
        {
            smallest = index;
        }
    }

    int newIndex = smallest;
    shortPath = minHeap -> array[smallest] -> path;

    if(minHeap -> size > right)
    {
        if(minHeap -> array[right] -> path < shortPath)
        {
            smallest = right;
        }
        else
        {
            smallest = newIndex;
        }
    }
    
    smallestNode = minHeap -> array[smallest];
    indexNode = minHeap -> array[index];

    if(smallest != index)
    {
        (*pos)[smallestNode -> vertex] = index;
        (*pos)[indexNode -> vertex] = smallest;

        swapPath(&minHeap -> array[smallest], &minHeap -> array[index]);
        downHeapify(minHeap, pos, length, smallest);
    }
    return;
}

void update(struct MinHeap* minHeap, int dest, int path, int pos, int **posArray)
{
    int parent;
    int child;
    int pIndex;
    int cIndex;
    int index = pos;
    minHeap -> array[index] -> path = path;

    while(index > 0)
    {
        parent = (index - 1) / 2;
        child = index;

        if(minHeap -> array[parent] -> path > minHeap -> array[child] -> path)
        {
            pIndex = minHeap -> array[parent] -> vertex;
            cIndex = minHeap -> array[child] -> vertex;

            (*posArray)[pIndex] = parent;
            (*posArray)[cIndex] = child;

            swapPath(&minHeap -> array[child], &minHeap -> array[parent]);
        }
        index = (index - 1) / 2;
    }
    return;
}

bool isEmpty(struct MinHeap* minHeap)
{
    if(minHeap -> size != 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool inQueue(struct MinHeap* minHeap, int i)
{
    if(i < minHeap -> size)
    {
        return true;
    }
    else
    {
        return false;
    }
}

