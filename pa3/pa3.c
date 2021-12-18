#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "matrix.h"
#include "adjList.h"
#include "minheap.h"

void dijkstra(struct Matrix* grid , int src, int pred[], int dist[])
{
	
	return;
}

void writePath(int parent[], int index, int *length, int r, int c, FILE* output)
{
    if (parent[index] == - 1)
    {
        return;
    }

	short row = index / c;
	short col = index;

	while (col > c)
	{
		col -= c;
	}
	if (col == c)
	{
		col = 0;
	}

	fwrite(&row, sizeof(short), 1, output);
	fwrite(&col, sizeof(short), 1, output);

    writePath(parent, parent[index], length, r, c, output);
	*length += 1;
}

void writeGrid(short r, short c, short *grid, FILE* output)
{
    
}

void printGrid(short r, short c, short *grid)
{
    
}

void printArr(int dist[], int n)
{
	printf("Distance from Source\n");
    int i;
	for (i = 0; i < n; ++i)
    {
        printf("%d \t\t %d\n", i, dist[i]);
    }
}


int main(int argc, char* argv[])
{
    
}