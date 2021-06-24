#include <stdio.h>
#include <stdlib.h>
#include "bfsdfs.h"
int main()
{
    Graph g;
    int *v = (int *)malloc(10001*sizeof(int));
    int count;

    g = creatGraph();
    addEdge(g, 0, 4);
    addEdge(g, 2, 4);
    addEdge(g, 1, 4);
    addEdge(g, 3, 4);
    addEdge(g, 1, 2);
    addEdge(g, 2, 3);
    addEdge(g, 4, 5);
    addEdge(g, 5, 6);

    count = BFS(g, v);
    printf("\n");
    xuatFilebfs(v, count);

    count = DFS(g, v);
    printf("\n");
    xuatFiledfs(v, count);

    fileOriginal(g);
    free(v);
    dropGraph(g);
    return 0;
}
