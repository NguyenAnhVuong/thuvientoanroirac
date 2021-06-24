#include"dag.h"
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
void addEdge(Graph g, int v1, int v2)
{
    JRB tree = make_jrb();
    JRB tmp = jrb_find_int(g.edges, v1);
    if(tmp == NULL)
    {
        jrb_insert_int(g.edges, v1, new_jval_v(tree));
        jrb_insert_int(tree, v2, new_jval_i(1));
    }
    else
    {
        tmp = (JRB)tmp->val.v;
        jrb_insert_int(tmp, v2, new_jval_i(1));
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
    int count = 0;
    jrb_traverse(tmp, g.edges)
    {
        if(tmp->key.i != v)
        {
            int a = tmp->key.i;
            tmp = (JRB)tmp->val.v;
            tmp1 = jrb_find_int(tmp, v);
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
    int n = 0;
    int clock = 1;
    int *visited =(int *)calloc(10001, sizeof(int));
    int u;
    JRB tmp1;
    jrb_traverse(tmp, g1.vertices)
    {
        if(visited[tmp->key.i] == 0)
        {
            explore(g1, visited, tmp->key.i, &clock);
        }
    }
}
void DAG(Graph g)
{
    int u;
    int *output = (int *)malloc(10001 *sizeof(int));
    pre = (int *)malloc(10001 *sizeof(int));
    post = (int *)malloc(10001 *sizeof(int));
    JRB tmp;
    int n;
    Queue q;
    int check = -1;
    int zzz = 0;
    jrb_traverse(tmp, g.vertices)
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
                    if(visited[output[i]] == 0)enQueue(&q, output[i]);
                    if(output[i] == tmp->key.i && zzz == 0)
                    {
                        check = tmp->key.i;
                        zzz = 1;
                    }

                }
            }
            visited[u] = 1;
        }
    }
    if(check == -1)
    {
        printf("Do thi khong co chu trinh\n");
        return;
    }
    else
    {
        printf("Do thi co chu trinh\n");
    }
    JRB tmp1;
    JRB tmp2;
    int *tt = (int *)malloc(10001 *sizeof(int));
    Graph gr = createGraph();
    int sd = 0;
    jrb_traverse(tmp, g.vertices)
    {
        addVertex(gr, tmp->key.i, "");
        sd++;
    }
    jrb_traverse(tmp, g.edges)
    {
        tmp1 = (JRB)tmp->val.v;
        jrb_traverse(tmp2, tmp1)
        {
            addEdge(gr, tmp2->key.i, tmp->key.i);
        }
    }
    DFS(gr);
    for(int i = 0; i < sd; i++)
    {
        tt[i] = i;
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
    int *xx = (int *)malloc(10001 *sizeof(int));
    int nn = 0;
    int *visited1 = (int *)calloc(10001, sizeof(int));
    for(int i = 0; i < sd; i++)
    {
        if(visited1[tt[i]] == 0)
        {
            makeNullQueue(&q);
            enQueue(&q, tt[i]);
            while(!isEmpty(q))
            {
                deQueue(&q, &u);
                if(visited1[u] == 0)
                {
                    n = outdegree(g, u, output);
                    if(tt[i] == check)
                    {
                        xx[nn++] = u;
                    }
                    for(int j = 0; j < n; j++)
                    {
                        if(visited1[output[j]] == 0)
                        {
                            enQueue(&q, output[j]);
                        }
                    }
                    visited1[u] = 1;
                }
            }
        }
    }

    free(visited1);
    FILE *fp = fopen("dag.dot", "w");
    if(fp == NULL)
    {
        printf("Co loi khi mo file!\n");
        exit(0);
    }
    fprintf(fp, "digraph dothi\n{\n");
    jrb_traverse(tmp, g.vertices)
    {
        int kt = 1;
        for(int i = 0; i < nn; i++)
        {
            if(xx[i] == tmp->key.i)kt = 0;
        }
        if(kt == 1)
        {
            fprintf(fp, "%d [fillcolor=white, style=filled];\n", tmp->key.i);
        }
        else
        {
            fprintf(fp, "%d [fillcolor=red, style=filled];\n", tmp->key.i);
        }
    }


    jrb_traverse(tmp, g.edges)
    {
        tmp1 = (JRB)tmp->val.v;
        jrb_traverse(tmp2, tmp1)
        {
            fprintf(fp, "%d -> %d;\n", tmp->key.i, tmp2->key.i);
        }
    }
    fprintf(fp, "}");
    free(output);
    free(xx);
    fclose(fp);
}
