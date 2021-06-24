#include "topo.h"
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
int DAG(Graph g)
{

    int u;
    int *output = (int *)malloc(10001 * sizeof(int));
    JRB tmp;
    int n;
    Queue q;
    jrb_traverse(tmp, g.edges)
    {
        int *visited = (int *)calloc(10001, sizeof(int));
        makeNullQueue(&q);
        enQueue(&q, tmp->key.i);
        while(!isEmpty(q))
        {
            deQueue(&q, &u);
            if(visited[u] == 0)
            {
                n = outdegree(g, u, output);

                for(int i = 0; i < n; i++)
                {
                    enQueue(&q, output[i]);
                    if(output[i] == tmp->key.i)return 0;

                }
            }
            visited[u] = 1;
        }
        free(visited);

    }
    free(output);
    return 1;
}
void xuatFILE(Graph g, char *filename, int output[])
{
    FILE *fp = fopen(filename,"w");
    if(fp == NULL){
        printf("Can't open file!!!\n");
        return;
    }

    else{
        fprintf(fp,"digraph dothi\n{\n");
        for(int i = 0; i < 6; i++){
            fprintf(fp, "%d [fillcolor = white, style = filled, label = %s];\n", i, getVertex(g, i));
        }
        for(int i = 0; i < 5; i++){
            fprintf(fp, "%d -> %d;\n", output[i], output[i+1]);
        }
        fprintf(fp, "}");
    }
    fclose(fp);
}
void topologicalSort(Graph g,int *output,int *n)
{
    if (!DAG(g))
    {
        printf("Can not make topological sort\n");
        return ;
    }
    JRB tmp;
    int *dk = (int *)calloc(10001, sizeof(int));
    int *out = (int *)malloc(10001 * sizeof(int));
    Queue q;
    makeNullQueue(&q);
    int u, m;
    *n = 0;
    jrb_traverse(tmp, g.vertices)
    {
        dk[tmp->key.i] = indegree(g, tmp->key.i, out);
        if(dk[tmp->key.i] == 0)enQueue(&q, tmp->key.i);

    }
    while(!isEmpty(q))
    {
        deQueue(&q, &u);
        output[(*n)++] = u;
        m = outdegree(g, u, out);
        for(int i = 0; i < m; i++)
        {
            dk[out[i]]--;
            if(dk[out[i]] == 0)enQueue(&q, out[i]);
        }

    }
    xuatFILE(g, "dothitopo.dot", output);
    free(dk);
    free(out);
}
void xuatdothigoc(Graph g)
{
    JRB tmp, tmp1, tmp2;
    FILE *fp = fopen("dothi.dot", "w");
    if(fp == NULL)
    {
        printf("Co loi khi mo file!\n");
        exit(0);
    }
    fprintf(fp, "digraph dothi\n{\n");
    jrb_traverse(tmp, g.vertices)
    {
        fprintf(fp, "%d [fillcolor=white, style=filled, label = %s];\n", tmp->key.i, getVertex(g, tmp->key.i));
    }
    jrb_traverse(tmp, g.edges)
    {
        tmp1 = tmp->val.v;
        jrb_traverse(tmp2, tmp1)
        {
            fprintf(fp, "%d -> %d\n", tmp->key.i, tmp2->key.i);
        }
    }
    fprintf(fp, "}");
    fclose(fp);
}
