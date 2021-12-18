#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "matrix.h"
#include "adjacencyList.h"
#include "minHeap.h"

void Dijkstra(struct Matrix* graph , int src, int pred[], int dist[])
{
    int size;
    int i;
    int vertIndex;
    int dest;
    int newWeight;
    int *pos = (int *)malloc(size * sizeof(int));

    size = graph -> numV;
    struct MinHeap* minHeap = makeHeap(size);

    for(i = 0; i < size; i++)
    {
        dist[i] = INT_MAX;
        pred[i] = -1;
        pos[i];
    }

    dist[src] = 0;
    minHeap -> array[src] -> dist = 0;
    pos[minHeap->array[src]->vertex] = 0;
    pos[minHeap -> array[0] -> vertex] = src;
    swapPath(&minHeap -> array[src], &minHeap -> array[0]);

    struct AdjList* adj = NULL;
    struct AdjacencyNode* edge = NULL;
    struct Path* minPath = NULL;
    
    while(!(isEmpty(minHeap)))
    {
        minPath = extract(minHeap, &pos, size);
        vertIndex = minPath -> vertex;
        adj = graph -> list;
        edge = adj[vertIndex].head;

        while(edge != NULL)
        {
            dest = edge -> dest;
            newWeight = edge -> weight + dist[vertIndex];

            if(dist[dest] > newWeight && inQueue(minHeap, pos[dest]))
            {
                dist[dest] = newWeight;
                update(minHeap, dist[dest], pos[dest], &pos);
                pred[dest] = vertIndex;
            }
            edge = edge -> next;
        }

        free(minPath);
    }
    free(minHeap -> array);
    free(minHeap);
    free(pos);
	return;
}

void pathWrite(int parent[], int index, int *length, int row, int col, FILE* output)
{
    if (parent[index] == - 1)
    {
        return;
    }

	short rows = index / col;

	int cols = index;
	while (cols > col && (cols - col >= 0))
	{
		cols -= col;
	}
	if (cols == col)
	{
		cols = 0;
	}
	short column = cols;

	fwrite(&rows, sizeof(short), 1, output);
	fwrite(&column, sizeof(short), 1, output);

    pathWrite(parent, parent[index], length, row, col, output);
	*length += 1;
}

void gridWrite(short row, short col, short *grid, FILE* output)
{
    int i;
    int counter = 0;

    printf(output, "%d %d\n", row, col);

    for (i = 0; i < row * col; i++)
    {
        if (counter % col != 0)
        {
            fprintf(output, " ");
        }
        if (counter == col)
        {
            fprintf(output, "\n");
            counter = 0;
        }
        fprintf(output, "%d", grid[i]);
        counter += 1;
    }
    fprintf(output, "\n");
}

int main(int argc, char* argv[])
{
    if (argc != 5)
    {
        return EXIT_FAILURE;
    }

    FILE* input = fopen(argv[1], "rb");

    if (input == NULL)
    {
        return EXIT_FAILURE;
    }

    short row = 0;
    short col = 0;
    fread(&row, sizeof(row), 1, input);
    fread(&col, sizeof(col), 1, input);

    short *grid = (short *)malloc((row * col) * sizeof(short *));

    int i = 0;
    short temp = 0;

    for (i = 0; i < row * col; i++)
    {
        fread(&temp, sizeof(short), 1, input);
        grid[i] = temp;
    }

    FILE* inputText = fopen(argv[2], "w");
    if (inputText == NULL)
    {
        return EXIT_FAILURE;
    }
    gridWrite(row, col, grid, inputText); 

    int v;
    v = row * col;
    struct Matrix* graph = makeGraph(v + 1);

    for (i = 0; i < v; i++)
    {
        if (i - col >= 0) // up
        {
            addEdge(graph, i, i - col, grid[i - col]);
        }

        if (i + row < row * col) // down
        {
            addEdge(graph, i, i + col, grid[i + col]);
        }

        if (i % col != 0) // left side
        {
            addEdge(graph, i, i-1, grid[i - 1]);
        }

        if ((i + 1) % col != 0) // right side
        {
            addEdge(graph, i, i + 1, grid[i + 1]);
        }
    }

    for (i = v - col; i < v; i++)
    {
        addEdge(graph, v, i, grid[i]);
    }

    int *dist = (int*)malloc(v * sizeof(int*));
    int *parent = (int*)malloc(v * sizeof(int*));

    Dijkstra(graph, v, parent, dist);

    int index;

    for (i = 1; i < col; i++)
    {
        if (dist[i] <= dist[index])
        {
            index = i;
        }
    }

    int length = 0;
    int j = index;

    while (parent[j] != -1)
    {
        length += 1;
        j = parent[j];
    }

    FILE* fastestTime = fopen(argv[3], "wb");
    if (fastestTime == NULL)
    {
        return EXIT_FAILURE;
    }
    fwrite(&col, sizeof(col), 1, fastestTime);
    
    for (i = 0; i < col; i++)
    {
        fwrite(&dist[i], sizeof(dist[i]), 1, fastestTime);
    }

    FILE* fastestPath = fopen(argv[4], "wb");
    if (fastestPath == NULL)
    {
        return EXIT_FAILURE;
    }
    fwrite(&dist[index], sizeof(dist[index]), 1, fastestPath);
    fwrite(&length, sizeof(length), 1, fastestPath);
	pathWrite(parent, index, &length, row, col, fastestPath);

    int d;
    for (d = 0; d < graph -> numV; d++)
    {
        struct AdjacencyNode *current = graph -> list[d].head, *next;
        while(current)
        {
            next = current;
            current = current -> next;
            free(next);
        }
    }

    free(graph -> list);
    free(graph);
    free(grid);
    free(dist);
    free(parent);

    fclose(input);
    fclose(inputText);
    fclose(fastestTime);
    fclose(fastestPath);

    return EXIT_SUCCESS;
}
