#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jrb.h"
#include "queue.h"
#include "stack.h"
typedef JRB Graph;
Graph creatGraph();
void addEdge(Graph g, int v1, int v2);
int adjacent(Graph g, int v1, int v2);
int getAdjacentVertices(Graph g, int v, int *output);
void dropGraph(Graph g);
int BFS(Graph g, int v[]);
int DFS(Graph g, int v[]);
void fileOriginal(Graph g);
void xuatFilebfs(int v[], int count);
void xuatFiledfs(int v[], int count);
