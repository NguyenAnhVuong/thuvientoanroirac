#include <stdio.h>
#include <stdlib.h>
#include "jrb.h"
#include "queue.h"
#include <string.h>
int *pre;
int *post;
typedef struct
{
    JRB edges;
    JRB vertices;
} Graph;
Graph createGraph();

void addVertex(Graph g, int id, char *name);
char *getVertex(Graph g, int id);
void addEdge(Graph g, int v1, int v2);
int hasEdge(Graph g, int v1, int v2);
int indegree(Graph g, int v, int* output);
int outdegree(Graph g, int v, int* output);
void explore(Graph g1, int *visited, int v, int *clock);
void DFS(Graph g1);
void DAG(Graph g);
