#include "bellman.h"
Graph createGraph()
{
    Graph g;
    g.edges = make_jrb();
    g.vertices = make_jrb();
    return g;
}
void addVertex(Graph g, int id, char *name)
{
    JRB tmp = jrb_find_int(g.vertices, id);
    if(tmp == NULL)
    {
        jrb_insert_int(g.vertices, id, new_jval_s(strdup(name)));
    }
    else
    {
        strcpy(tmp->val.s, name);
    }
}
char *getVertex(Graph g, int id)
{
    JRB tmp = jrb_find_int(g.vertices, id);
    return tmp->val.s;
}
void addEdge(Graph g, int v1, int v2, int kc)
{
    JRB tree = make_jrb();
    JRB tmp = jrb_find_int(g.edges, v1);
    JRB tmp1;
    if(tmp == NULL)
    {
        jrb_insert_int(g.edges, v1, new_jval_v(tree));
        jrb_insert_int(tree, v2, new_jval_i(kc));
    }
    else
    {
        tmp = (JRB)tmp->val.v;
        tmp1 = jrb_find_int(tmp, v2);
        if(tmp1 == NULL)jrb_insert_int(tmp, v2, new_jval_i(kc));
    }
}
int hasEdge(Graph g, int v1, int v2)
{
    JRB tmp = jrb_find_int(g.edges, v1);
    if(tmp == NULL)
    {
        return 0;
    }
    else
    {
        tmp =  (JRB)tmp->val.v;
        JRB tmp1 = jrb_find_int(tmp, v2);
        if(tmp1 != NULL)return 1;
        return 0;
    }
}
int indegree(Graph g, int v, int* output)
{
    JRB tmp;
    JRB tmp1;
    JRB tmp2;
    int count = 0;
    int a;
    jrb_traverse(tmp, g.edges)
    {

        if(tmp->key.i != v)
        {
            a = tmp->key.i;
            tmp2 = (JRB)tmp->val.v;
            tmp1 = jrb_find_int(tmp2, v);
            if(tmp1 != NULL)
            {
                output[count++] = a;
            }
        }
    }
    return count;
}
int outdegree(Graph g, int v, int* output)
{
    JRB tmp = jrb_find_int(g.edges, v);
    int count = 0;
    JRB tmp1;
    if(tmp != NULL)
    {
        tmp = (JRB)tmp->val.v;
        jrb_traverse(tmp1, tmp)
        {
            output[count++] = tmp1->key.i;
        }
    }
    return count;
}
void xuatFiledijkstra(Graph g, int instruc[], int x)
{
    FILE *fp = fopen("bell.dot", "w");
    JRB tree;
    int output[9000];
    int n;

    if(fp == NULL)
    {
        printf("Khong mo duoc file!!!\n");
        return;
    }
    else
    {
        int count = 0;
        fprintf(fp, "digraph dothi\n{\n");
        jrb_traverse(tree, g.vertices)
        {
            if(tree->key.i == instruc[0] || tree->key.i == instruc[x -1])
            {
                fprintf(fp, "%d [fillcolor = yellow, style = filled, label = %s];\n", tree->key.i, tree->val.s);
            }
            else
            {
                fprintf(fp, "%d [fillcolor = white, style = filled, label = %s];\n", tree->key.i, tree->val.s);
            }
        }
        jrb_traverse(tree, g.edges)
        {
            int k = 1;
            n = outdegree(g, tree->key.i, output);
            for(int i = 0; i < n; i++)
            {
                for(int j = x;  j >= 0; j--)
                {
                    if(tree->key.i == instruc[j] && output[i] == instruc[j-1])
                    {
                        fprintf(fp, "%d -> %d [label = %d , color = green];\n", tree->key.i, output[i], hasEdge(g, tree->key.i, output[i]));
                        k = -1;
                    }
                }
                if(k > 0) fprintf(fp, "%d -> %d [label = %d];\n", tree->key.i, output[i], hasEdge(g, tree->key.i, output[i]));
            }
        }
        fprintf(fp, "}");
    }
    fclose(fp);
}
void BellmanFord(Graph g, int diemdau, int diemcuoi, int arr[])
{
    int V = 0;
    JRB tmp, tmp1, tmp2;
    jrb_traverse(tmp, g.vertices)
    {
        V++;
    }
    int *diemtruoc = (int *)malloc(10001 * sizeof(int));
    //printf("%d\n", V);
    int *StoreDistance = (int *)malloc(10001 * sizeof(int));
    for (int i = 1; i <= V; i++)
    {
        StoreDistance[i] = 1000000;
    }
    StoreDistance[diemdau] = 0;
    for (int i = 1; i <= V-1; i++)
    {
        jrb_traverse(tmp, g.edges)
        {
            tmp1 = (JRB)tmp->val.v;
            jrb_traverse(tmp2, tmp1)
            {
                int u = tmp->key.i;
                int v = tmp2->key.i;
                int weight = tmp2->val.i;
                //printf("**%d %d %d\n", u, v, weight);
                if (StoreDistance[u] + weight < StoreDistance[v])
                {
                    StoreDistance[v] = StoreDistance[u] + weight;
                    diemtruoc[v] = u;
                    //printf("***%d %d\n", v, StoreDistance[v]);
                }
            }
        }
    }
    printf("%-5s\t%-10s\n", "Dinh", "Khoang cach den nguon");
    int check = 1;
    for(int i = 1; i <= V; i++)
    {
        printf("%-5d\t          %d\n", i, StoreDistance[i]);
        if(StoreDistance[i] == 1000000)check = 0;
    }
    jrb_traverse(tmp, g.edges)
    {
        tmp1 = (JRB)tmp->val.v;
        jrb_traverse(tmp2, tmp1)
        {
            int u = tmp->key.i;
            int v = tmp2->key.i;
            int weight = tmp2->val.i;
            if (StoreDistance[u] + weight < StoreDistance[v])
            {
                printf("Do co chua chu trinh am\n");
                check = 0;
            }
        }
    }
    if(check == 1)
    {
        int x = 0;
        if(StoreDistance[diemcuoi] == 100000)
        {
            printf("khong co duong!\n");
            return;
        }
        int m = diemcuoi;
        while(m != diemdau)
        {
            arr[x++] = m;
            m = diemtruoc[m];
        }
        arr[x++] = diemdau;
        x;
        for(int i = x - 1; i >= 0; i--)
        {
            printf("%s ", getVertex(g, arr[i]));
        }
        printf("\n");
        xuatFiledijkstra(g, arr, x);
    }
}
