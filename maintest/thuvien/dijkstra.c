#include "dijkstra.h"
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
    if(tmp == NULL)
    {
        jrb_insert_int(g.edges, v1, new_jval_v(tree));
        jrb_insert_int(tree, v2, new_jval_i(kc));
    }
    else
    {
        tmp = (JRB)tmp->val.v;
        jrb_insert_int(tmp, v2, new_jval_i(kc));
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
        if(tmp1 != NULL)return tmp1->val.i;
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
void xuatFiledijkstra(Graph g, int instruc[], int x){
    FILE *fp = fopen("dijkstra.dot", "w");
    JRB tree;
    int output[9000];
    int n;

    if(fp == NULL){
        printf("Khong mo duoc file!!!\n");
        return;
    }
    else{
        int count = 0;
        fprintf(fp, "digraph dijkstra\n{\n");
        jrb_traverse(tree, g.vertices){
            if(tree->key.i == instruc[0] || tree->key.i == instruc[x -1]){
                fprintf(fp, "%d [fillcolor = yellow, style = filled, label = %s];\n", tree->key.i, tree->val.s);
            }
            else{
                fprintf(fp, "%d [fillcolor = white, style = filled, label = %s];\n", tree->key.i, tree->val.s);
            }
        }
        jrb_traverse(tree, g.edges){
            int k = 1;
            n = outdegree(g, tree->key.i, output);
            for(int i = 0; i < n; i++){
                for(int j = x;  j >= 0; j--){
                    if(tree->key.i == instruc[j] && output[i] == instruc[j-1]){
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
void  edgesDijkstra(Graph g, int diemdau, int diemcuoi, int sodinh, int arr[])
{
    int *d = (int *)malloc(sodinh * sizeof(int)); //khoang cach tu diem dau
    for(int i = 0; i < sodinh; i++)
    {
        d[i] = 100000;
    }
    d[diemdau] = 0;
    int *diemtruoc = (int *)malloc(sodinh * sizeof(int));
    int *check = (int *)calloc(sodinh, sizeof(int)); //visited
    Queue q;
    makeNullQueue(&q);
    enQueue(&q, diemdau);
    int u;
    int n;
    int output[9000];
    JRB tmp, tmp1, tmp2;
    while(!isEmpty(q))
    {
        deQueue(&q, &u);
        n = outdegree(g, u, output);
        tmp = jrb_find_int(g.edges, u);
        if(check[u] == 0)
        {
            for(int i = 0; i < n; i++)
            {
                enQueue(&q, output[i]);
                tmp1 = (JRB)tmp->val.v;
                tmp2 = jrb_find_int(tmp1, output[i]);
                if(d[output[i]] == 100000)
                {
                    d[output[i]] = tmp2->val.i + d[u];
                    diemtruoc[output[i]] = u;
                }
                else if(tmp2->val.i + d[u] < d[output[i]])
                {
                    d[output[i]] = tmp2->val.i + d[u];
                    diemtruoc[output[i]] = u;
                }

            }
        }
        check[u] = 1;
    }
    if(d[diemcuoi] == 100000)
    {
        printf("Khong co duong!\n");
        return;
    }
    int x = 0;
    int m = diemcuoi;
    while(m != diemdau)
    {
        arr[x++] = m;
        m = diemtruoc[m];
    }
    arr[x++] = diemdau;
    //arr[100] = x;
    for(int i = x - 1; i >= 0; i--)
    {
        printf("%s ", getVertex(g, arr[i]));
    }
    printf("\n");
    xuatFiledijkstra(g, arr, x);
}

