#include <stdio.h>
#include <stdlib.h>
#include "dag.h"
int main()
{
    Graph g = createGraph();
    addVertex(g, 0, "");
    addVertex(g, 1, "");
    addVertex(g, 2, "");
    addVertex(g, 3, "");
    addEdge(g, 0, 1);
    addEdge(g, 1, 2);
    addEdge(g, 2, 0);
    addEdge(g, 1, 3);
    DAG(g);
    return 0;
}
