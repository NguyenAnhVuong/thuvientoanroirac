#include <stdio.h>
#include <stdlib.h>
#include "topo.h"
int main()
{
    int *output = (int *)malloc(10001 * sizeof(int));
    int n;
    Graph g = createGraph();
    addVertex(g, 0, "CS102");
    addVertex(g, 1, "CS140");
    addVertex(g, 2, "CS160");
    addVertex(g, 3, "CS302");
    addVertex(g, 4, "CS311");
    addVertex(g, 5, "MATH300");
    addEdge(g, 0, 1, 1);
    addEdge(g, 0, 2, 1);
    addEdge(g, 1, 3, 1);
    addEdge(g, 5, 4, 1);
    addEdge(g, 3, 4, 1);
    xuatdothigoc(g);
    topologicalSort(g, output, &n);
    printf("The topological order:\n");
    for (int i=0; i<n; i++)
    {
        printf("%s\n", getVertex(g, output[i]));
    }
    return 0;
}
