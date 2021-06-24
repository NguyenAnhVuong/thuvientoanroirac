#include <stdio.h>
#include <stdlib.h>
#include "dijkstra.h"
int main()
{
    Graph g = createGraph();
    int *instruction = (int *)malloc(10001 * sizeof(int));

    addVertex(g, 0, "A");
    addVertex(g, 1, "B");
    addVertex(g, 2, "C");
    addVertex(g, 3, "D");
    addVertex(g, 4, "E");
    addVertex(g, 5, "F");
    addEdge(g, 0, 1, 3);
    addEdge(g, 0, 2, 1);
    addEdge(g, 1, 3, 5);
    addEdge(g, 1, 4, 1);
    addEdge(g, 2, 1, 7);
    addEdge(g, 2, 3, 4);
    addEdge(g, 3, 4, 7);
    addEdge(g, 2, 5, 1);
    addEdge(g, 5, 3, 2);

    edgesDijkstra(g, 0, 3, 6, instruction);
    return 0;
}
