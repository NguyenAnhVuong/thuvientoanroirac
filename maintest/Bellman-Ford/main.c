#include <stdio.h>
#include <stdlib.h>
#include "bellman.h"
int main()
{
    Graph g = createGraph();
    int *instruction = (int *)malloc(10001 * sizeof(int));
    addVertex(g, 1, "A");
    addVertex(g, 2, "B");
    addVertex(g, 3, "C");
    addVertex(g, 4, "D");
    addVertex(g, 5, "E");
    addVertex(g, 6, "F");
    addVertex(g, 7, "G");
    addVertex(g, 8, "S");
    addEdge(g, 1, 5, 2);
    addEdge(g, 2, 1, 1);
    addEdge(g, 2, 3, 1);
    addEdge(g, 3, 4, 3);
    addEdge(g, 4, 5, -1);
    addEdge(g, 5, 2, -2);
    addEdge(g, 6, 5, -1);
    addEdge(g, 6, 1, -4);
    addEdge(g, 7, 6, 1);
    addEdge(g, 8, 7, 8);
    addEdge(g, 8, 1, 10);
    BellmanFord(g, 8, 5, instruction);
    return 0;
}
