#include "lienthongmanh.h"
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
void explore(Graph g1, int *visited, int v, int *clock)
{
    visited[v] = 1;
    pre[v] = (*clock)++;
    JRB tmp = jrb_find_int(g1.edges, v);
    JRB tmp1;
    JRB tmp2;
    if(tmp != NULL)
    {
        tmp1 = (JRB)tmp->val.v;
        jrb_traverse(tmp2, tmp1)
        {
            if(visited[tmp2->key.i] == 0)explore(g1, visited, tmp2->key.i, clock);
        }
    }
    post[v] = (*clock)++;
}
void DFS(Graph g1)
{
    JRB tmp;

    int clock = 1;
    int *visited =(int *)calloc(10001, sizeof(int));

    jrb_traverse(tmp, g1.vertices)
    {
        if(visited[tmp->key.i] == 0)
        {
            explore(g1, visited, tmp->key.i, &clock);
        }
    }
}


void sothanhphanlienthongmanh(Graph g)
{
    Graph gr = createGraph();
    char color[20][20] = {"red", "green", "blue","yellow","orange","purple","gray","pink","brown", "white"};
    pre = (int *)malloc(10001 *sizeof(int));
    post = (int *)malloc(10001 *sizeof(int));
    int count = 0;
    JRB tmp, tmp1, tmp2;
    int * tt = (int *)malloc(10001 *sizeof(int));
    int *visited = (int *)calloc(10001, sizeof(int));
    int *output = (int *)malloc(10001 *sizeof(int));;

    int sd = 0;
    jrb_traverse(tmp, g.vertices)
    {
        sd++;
        addVertex(gr, tmp->key.i, "");
    }
    jrb_traverse(tmp, g.edges)
    {
        tmp1 = (JRB)tmp->val.v;
        jrb_traverse(tmp2, tmp1)
        {
            addEdge(gr, tmp2->key.i, tmp->key.i, 1);
        }
    }
    DFS(gr);
    for(int i = 0; i < sd; i++)
    {
        tt[i] = i + 1;
    }
    for(int i = 0; i < sd - 1; i++)
    {
        for(int j = i + 1; j < sd; j++)
        {
            if(post[tt[i]] < post[tt[j]])
            {
                int a = tt[i];
                tt[i] = tt[j];
                tt[j] = a;
            }
        }
    }
    Queue q;
    int u;
    int n;

    FILE *fp = fopen("stpltm.dot", "w");
    if(fp == NULL)
    {
        printf("Co loi khi mo file!\n");
        exit(0);
    }
    fprintf(fp, "digraph dothi\n{\n");

    for(int i = 0; i < sd; i++)
    {
        if(visited[tt[i]] == 0)
        {
            count++;
            makeNullQueue(&q);
            enQueue(&q, tt[i]);
            //printf("%s\n", getVertex(g, tt[i]));
            while(!isEmpty(q))
            {
                deQueue(&q, &u);
                if(visited[u] == 0)
                {
                    if(count < 11)fprintf(fp, "%d [fillcolor=%s, style=filled];\n", u, color[count - 1]);
                    else fprintf(fp, "%d [fillcolor=white, style=filled];\n", u);
                    n = outdegree(g, u, output);
                    for(int j = 0; j < n; j++)
                    {
                        if(visited[output[j]] == 0)
                        {
                            enQueue(&q, output[j]);
                        }
                    }
                    visited[u] = 1;
                }
            }
        }
    }
    printf("So thanh phan lien thong manh: %d\n", count);
    jrb_traverse(tmp, g.edges)
    {
        tmp1 = (JRB)tmp->val.v;
        jrb_traverse(tmp2, tmp1)
        {
            fprintf(fp,"%d -> %d;\n", tmp->key.i, tmp2->key.i);
        }
    }
    fprintf(fp, "}");
    fclose(fp);
    free(visited);
    free(tt);
    free(pre);
    free(post);
    free(output);
}
