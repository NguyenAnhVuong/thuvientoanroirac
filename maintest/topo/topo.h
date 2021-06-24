#include <stdio.h>
#include <stdlib.h>
#include "jrb.h"
#include "queue.h"
#include <string.h>
typedef struct
{
    JRB edges;
    JRB vertices;
} Graph;
Graph createGraph();
void addVertex(Graph g, int id, char *name);
char *getVertex(Graph g, int id);
void addEdge(Graph g, int v1, int v2, int kc);
int hasEdge(Graph g, int v1, int v2);
int indegree(Graph g, int v, int* output);
int outdegree(Graph g, int v, int* output);
int DAG(Graph g);
void xuatFILE(Graph g, char *filename, int output[]);
void topologicalSort(Graph g,int *output,int *n);
void xuatdothigoc(Graph g);
