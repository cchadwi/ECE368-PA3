#ifndef matrix
#define matrix
#include "gridTrav.h"
#include <stdlib.h>

struct Matrix 
{
    int vertex;
    struct GridTrav* list;
};

struct Matrix* createGraph(int vertex)
{
    struct Matrix* m = malloc(sizeof(struct Matrix));
    
};
