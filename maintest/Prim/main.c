#include <stdio.h>
#include <stdlib.h>
#include "prim.h"
int main()
{
    Graph g = createGraph();
    addVertex(g, 1, "A");
    addVertex(g, 2, "B");
    addVertex(g, 3, "C");
    addVertex(g, 4, "D");
    addVertex(g, 5, "E");
    addVertex(g, 6, "F");

    addEdge(g, 1, 3, 6);
    addEdge(g, 1, 2, 5);
    addEdge(g, 1, 4, 4);
    addEdge(g, 2, 1, 5);
    addEdge(g, 2, 3, 1);
    addEdge(g, 2, 4, 2);
    addEdge(g, 3, 1, 6);
    addEdge(g, 3, 2, 1);
    addEdge(g, 3, 4, 2);
    addEdge(g, 3, 5, 5);
    addEdge(g, 3, 6, 3);
    addEdge(g, 4, 1, 4);
    addEdge(g, 4, 2, 2);
    addEdge(g, 4, 3, 2);
    addEdge(g, 4, 6, 4);
    addEdge(g, 5, 3, 5);
    addEdge(g, 5, 6, 4);
    addEdge(g, 6, 3, 3);
    addEdge(g, 6, 4, 4);
    addEdge(g, 6, 5, 4);
    Graph g1 = createGraph();
    g1 = Prim(g, g1, 1);
    JRB tmp;
    JRB tmp1;
    JRB tmp2;
    jrb_traverse(tmp, g1.edges)
    {
        tmp1 = (JRB)tmp->val.v;
        jrb_traverse(tmp2, tmp1)
        {
            printf("%d -- %d\n", tmp->key.i, tmp2->key.i);
        }
    }
    xuatFile("dothi.dot", g);
    xuatFile("caybaotrumnhonhat.dot", g1);
    return 0;
}
