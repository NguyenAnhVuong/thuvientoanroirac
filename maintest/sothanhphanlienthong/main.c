#include <stdio.h>
#include <stdlib.h>
#include "tplienthong.h"
int main()
{
    Graph g;
    g = createGraph();
    addVertex(g, 1, "");
    addVertex(g, 2, "");
    addVertex(g, 3, "");
    addVertex(g, 4, "");
    addVertex(g, 5, "");
    addVertex(g, 6, "");
    addVertex(g, 7, "");
    addVertex(g, 8, "");
    addVertex(g, 9, "");
    addVertex(g, 10, "");
    addVertex(g, 11, "");
    addEdge(g, 1, 2, 1);
    addEdge(g, 2, 3, 1);
    addEdge(g, 3, 1, 1);
    addEdge(g, 2, 4, 1);
    addEdge(g, 2, 5, 1);
    addEdge(g, 5, 4, 1);
    addEdge(g, 5, 8, 1);
    addEdge(g, 4, 6, 1);
    addEdge(g, 4, 7, 1);
    addEdge(g, 10, 11, 1);
    sothanhphanlienthong(g);
    return 0;
}
